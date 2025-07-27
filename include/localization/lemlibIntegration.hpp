#pragma once

#include <math.h>
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"
#include "lemlib/chassis/odom.hpp"
#include "particle_filter.hpp"
#include "logger.hpp"


template<size_t N>
class UpgradedChassis: public lemlib::Chassis {
public:
    explicit UpgradedChassis(
        lemlib::Drivetrain drivetrain,
        lemlib::ControllerSettings linearSettings,
        lemlib::ControllerSettings angularSettings,
        lemlib::OdomSensors odomSensors,
        const std::vector<Distance*>& pfSensors, lemlib::DriveCurve* throttleCurve = &lemlib::defaultDriveCurve,
        lemlib::DriveCurve* steerCurve = &lemlib::defaultDriveCurve
    ) : Chassis(drivetrain, linearSettings, angularSettings, odomSensors, throttleCurve,
                        steerCurve), pf(ParticleFilter<N>(pfSensors)) {}

    void setPose(float x, float y, float theta, bool radians = false, bool resetParticles = true) {
        Chassis::setPose(x, y, theta, radians);
        if (resetParticles) {
            pf.initNormDist({x, y, getPose(true, true).theta});
        }
    }

    void mclUpdate() {
        uint64_t start = pros::micros();

        // Get the change in movement
        const lemlib::Pose before = getPose(true, true);
        lemlib::update();
        const lemlib::Pose change = getPose(true, true) - before;

        std::normal_distribution<> xDistribution(0, DRIVE_NOISE * std::fabs(change.x) + 0.001);
        std::normal_distribution<> yDistribution(0, DRIVE_NOISE * std::fabs(change.y) + 0.001);
        std::normal_distribution<> angleDistribution(0, ANGLE_NOISE * std::fabs(change.theta) + 0.001);

        static auto& randomGen = pf.getRandomGen();

        // No risk of dangling reference
        pf.update([&xDistribution, &yDistribution, &angleDistribution, &change]() {
            const auto noisyX = change.x + xDistribution(randomGen);
            const auto noisyY = change.y + yDistribution(randomGen);
            const auto noisyTheta = change.theta + angleDistribution(randomGen);

            return Eigen::Vector3f(noisyX, noisyY, noisyTheta);
        });

        // Set the pose to be the filters prediction
        const auto prediction = pf.getPrediction();
        setPose(prediction.x(), prediction.y(), M_PI_2 - prediction.z(), true, false);

        uint64_t duration = pros::micros() - start;
        logging::getLogger()->debug("MCL update took {} microseconds", duration);
        if (duration > 10000) {
            logging::getLogger()->warn("MCL update took too long");
        }
    }

    void initialize(const bool mcl) {
        if (sensors.imu != nullptr) {
            int attempt = 1;
            // calibrate inertial, and if calibration fails, then repeat 5 times or until successful
            while (attempt <= 5) {
                sensors.imu->reset();
                // wait until IMU is calibrated
                do pros::delay(10);
                while (sensors.imu->get_status() != pros::ImuStatus::error && sensors.imu->is_calibrating());
                // exit if imu has been calibrated
                if (!isnanf(sensors.imu->get_heading()) && !isinf(sensors.imu->get_heading())) {
                    break;
                }
                // indicate error
                logging::getLogger()->warn("IMU failed to calibrate! Attempt #{}", attempt);
                attempt++;
            }
            // check if calibration attempts were successful
            if (attempt > 5) {
                sensors.imu = nullptr;
                logging::getLogger()->error("IMU calibration failed, defaulting to tracking wheels / motor encoders");
                pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, "---");
            }
        }

        // initialize odom
        if (sensors.vertical1 == nullptr)
            sensors.vertical1 = new lemlib::TrackingWheel(drivetrain.leftMotors, drivetrain.wheelDiameter,
                                                          -(drivetrain.trackWidth / 2), drivetrain.rpm);
        if (sensors.vertical2 == nullptr)
            sensors.vertical2 = new lemlib::TrackingWheel(drivetrain.rightMotors, drivetrain.wheelDiameter,
                                                          drivetrain.trackWidth / 2, drivetrain.rpm);
        sensors.vertical1->reset();
        sensors.vertical2->reset();
        if (sensors.horizontal1 != nullptr) sensors.horizontal1->reset();
        if (sensors.horizontal2 != nullptr) sensors.horizontal2->reset();
        lemlib::setSensors(sensors, drivetrain);

        if (trackingTask == nullptr) {
            trackingTask = new pros::Task([this, mcl]() {
               while (true) {
                   if (mcl) {
                       mclUpdate();
                   }
                   else {
                       lemlib::update();
                   }

                   pros::delay(10);
               }
            });
        }

        // rumble to controller to indicate success
        pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, ".");
    }

protected:
    ParticleFilter<N> pf;
    pros::Task* trackingTask = nullptr;
};



