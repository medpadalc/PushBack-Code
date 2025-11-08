#pragma once

#include <math.h>
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"
#include "lemlib/chassis/odom.hpp"
#include "particleFilter.hpp"


namespace localization {

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

        std::uniform_real_distribution<> xDistribution(-DRIVE_NOISE * std::fabs(change.x), DRIVE_NOISE * std::fabs(change.x));
        std::uniform_real_distribution<> yDistribution(-DRIVE_NOISE * std::fabs(change.y), DRIVE_NOISE * std::fabs(change.y));
        std::uniform_real_distribution<> angleDistribution(-ANGLE_NOISE * std::fabs(change.theta), ANGLE_NOISE * std::fabs(change.theta));

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
        printf("MCL update took %llu microseconds, pose: (%.2f, %.2f, %.2f)\n", duration, prediction.x(), prediction.y(), (M_PI_2 - prediction.z()) * 180 / M_PI);
        if (duration > 10000) {
            printf("MCL Update took too long\n");
        }

    }

    void initialize(const bool mcl) {
        if (sensors.imu != nullptr) {
            int32_t result = sensors.imu->reset(true);
            // check if calibration attempts were successful
            if (result == PROS_ERR) {
                sensors.imu = nullptr;
                printf("IMU calibration failed, defaulting to tracking wheels / motor encoders");
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

}

