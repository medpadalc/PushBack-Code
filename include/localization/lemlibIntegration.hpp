#pragma once

#include <math.h>
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"
#include "lemlib/chassis/odom.hpp"
#include "lemlib/timer.hpp"
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

    void moveToPoint(float x, float y, int timeout, lemlib::MoveToPointParams params = {}, bool async = true) {
        params.earlyExitRange = fabs(params.earlyExitRange);
        this->requestMotionStart();
        // were all motions cancelled?
        if (!this->motionRunning) return;
        // if the function is async, run it in a new task
        if (async) {
            pros::Task task([&]() { moveToPoint(x, y, timeout, params, false); });
            this->endMotion();
            pros::delay(10); // delay to give the task time to start
            return;
        }

        // reset PIDs and exit conditions
        lateralPID.reset();
        lateralLargeExit.reset();
        lateralSmallExit.reset();
        angularPID.reset();

        // initialize vars used between iterations
        lemlib::Pose lastPose = getPose();
        distTraveled = 0;
        lemlib::Timer timer(timeout);
        bool close = false;
        float prevLateralOut = 0; // previous lateral power
        float prevAngularOut = 0; // previous angular power
        const int compState = pros::competition::get_status();
        std::optional<bool> prevSide = std::nullopt;

        // calculate target pose in standard form
        lemlib::Pose target(x, y);
        target.theta = lastPose.angle(target);

        // main loop
        while (!timer.isDone() && ((!lateralSmallExit.getExit() && !lateralLargeExit.getExit()) || !close) &&
               this->motionRunning) {
            // update position
            const lemlib::Pose pose = getPose(true, true);

            // update distance traveled
            distTraveled += pose.distance(lastPose);
            lastPose = pose;

            // calculate distance to the target point
            const float distTarget = pose.distance(target);

            // check if the robot is close enough to the target to start settling
            if (distTarget < 4.0 && close == false) {
                close = true;
                params.maxSpeed = fmax(fabs(prevLateralOut), 60);
            }

            // motion chaining
            const bool side =
                (pose.y - target.y) * -sin(target.theta) <= (pose.x - target.x) * cos(target.theta) + params.earlyExitRange;
            if (prevSide == std::nullopt) prevSide = side;
            const bool sameSide = side == prevSide;
            // exit if close
            if (!sameSide && params.minSpeed != 0) break;
            prevSide = side;

            // calculate error
            const float adjustedRobotTheta = params.forwards ? pose.theta : pose.theta + M_PI;
            const float angularError = lemlib::angleError(adjustedRobotTheta, pose.angle(target));
            float lateralError = pose.distance(target) * powf(cos(lemlib::angleError(pose.theta, pose.angle(target))), 11.0);

            // update exit conditions
            lateralSmallExit.update(lateralError);
            lateralLargeExit.update(lateralError);

            // get output from PIDs
            float lateralOut = lateralPID.update(lateralError);
            float angularOut = angularPID.update(lemlib::radToDeg(angularError));
            if (close) angularOut = 0;

            // apply restrictions on angular speed
            angularOut = std::clamp(angularOut, -params.maxSpeed, params.maxSpeed);
            angularOut = lemlib::slew(angularOut, prevAngularOut, angularSettings.slew);

            // apply restrictions on lateral speed
            lateralOut = std::clamp(lateralOut, -params.maxSpeed, params.maxSpeed);
            // constrain lateral output by max accel
            // but not for decelerating, since that would interfere with settling
            if (!close) lateralOut = lemlib::slew(lateralOut, prevLateralOut, lateralSettings.slew);

            // prevent moving in the wrong direction
            if (params.forwards && !close) lateralOut = std::fmax(lateralOut, 0);
            else if (!params.forwards && !close) lateralOut = std::fmin(lateralOut, 0);

            // constrain lateral output by the minimum speed
            if (params.forwards && lateralOut < fabs(params.minSpeed) && lateralOut > 0) lateralOut = fabs(params.minSpeed);
            if (!params.forwards && -lateralOut < fabs(params.minSpeed) && lateralOut < 0)
                lateralOut = -fabs(params.minSpeed);

            // update previous output
            prevAngularOut = angularOut;
            prevLateralOut = lateralOut;

            lemlib::infoSink()->debug("Angular Out: {}, Lateral Out: {}", angularOut, lateralOut);

            // ratio the speeds to respect the max speed
            float leftPower = lateralOut + angularOut;
            float rightPower = lateralOut - angularOut;
            const float ratio = std::max(std::fabs(leftPower), std::fabs(rightPower)) / params.maxSpeed;
            if (ratio > 1) {
                leftPower /= ratio;
                rightPower /= ratio;
            }

            // move the drivetrain
            drivetrain.leftMotors->move(leftPower);
            drivetrain.rightMotors->move(rightPower);

            // delay to save resources
            pros::delay(10);
        }

        // stop the drivetrain
        drivetrain.leftMotors->move(0);
        drivetrain.rightMotors->move(0);
        // set distTraveled to -1 to indicate that the function has finished
        distTraveled = -1;
        this->endMotion();
    }


protected:
    ParticleFilter<N> pf;
    pros::Task* trackingTask = nullptr;
};

}

