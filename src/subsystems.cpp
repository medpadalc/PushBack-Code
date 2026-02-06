#include "subsystems.hpp"

pros::Motor lowerIntakeMotor(1, pros::MotorGears::rpm_600);
pros::Motor upperIntakeMotor(-18, pros::MotorGears::rpm_600);

pros::adi::Pneumatics matchloadPiston('H',false);
pros::adi::Pneumatics middleGoalPiston('F', true, true);
pros::adi::Pneumatics wingPiston('G', false, false);
pros::adi::Pneumatics midGoalDescorePiston('E', false, false);

std::shared_ptr<pros::Task> intakingTaskPtr = nullptr;

void subsystems::intake::run(GoalType goalType) {
    if (intakingTaskPtr) {
        stop();
    }

    intakingTaskPtr = std::make_shared<pros::Task>([goalType]() {
        while (true) {
            iterate(goalType);
            pros::delay(10);
        }
    });
}

void subsystems::intake::iterate(GoalType goalType) {
    switch (goalType) {
        case GoalType::NONE:
            middleGoalPiston.extend();
            lowerIntakeMotor.brake();
            upperIntakeMotor.brake();
            break;
        case GoalType::LOW_GOAL:
            middleGoalPiston.extend();
            lowerIntakeMotor.move(-127);
            upperIntakeMotor.move(-127);
            break;
        case GoalType::MEDIUM_GOAL:
            middleGoalPiston.retract();
            lowerIntakeMotor.move_velocity(450);
            upperIntakeMotor.move(-127);
            break;
        case GoalType::HOLD_BALLS:
            middleGoalPiston.extend();
            lowerIntakeMotor.move(127);
            upperIntakeMotor.move_velocity(-100);
            break;
        case GoalType::LONG_GOAL:
            middleGoalPiston.extend();
            lowerIntakeMotor.move(127);
            upperIntakeMotor.move(127);
            break;
    }
}

void subsystems::intake::stop() {
    if (intakingTaskPtr) {
        intakingTaskPtr->remove();
        intakingTaskPtr = nullptr;
    }

    iterate(GoalType::NONE);
}

void subsystems::matchload::extend() {
    matchloadPiston.extend();
}

void subsystems::matchload::retract() {
    matchloadPiston.retract();
}

void subsystems::matchload::toggle() {
    matchloadPiston.toggle();
}

void subsystems::wing::extend() {
    wingPiston.extend();
}

void subsystems::wing::retract() {
    wingPiston.retract();
}

void subsystems::wing::toggle() {
    wingPiston.toggle();
}

void subsystems::midGoalDescore::extend() {
    midGoalDescorePiston.extend();
}

void subsystems::midGoalDescore::retract() {
    midGoalDescorePiston.retract();
}

void subsystems::midGoalDescore::toggle() {
    midGoalDescorePiston.toggle();
}

void subsystems::localization::leftDistanceReset(lemlib::Chassis& chassis, Wall wall) {
    static std::vector<pros::Distance> distanceSensors = pros::Distance::get_all_devices();
    if (distanceSensors.empty()) return;

    static pros::Distance leftDistanceSensor = distanceSensors[0];
    static double offset = 4.25;

    double distance = leftDistanceSensor.get() / 25.4;
    if (distance == 9999) return;

    double effectiveDistance = distance + offset;

    lemlib::Pose pose = chassis.getPose();
    double heading = pose.theta;

    switch (wall) {
        case Wall::LEFT_X:
            effectiveDistance *= std::cos(heading * (M_PI / 180));
            chassis.setPose(-70 + effectiveDistance, pose.y, pose.theta);
            break;
        case Wall::RIGHT_X:
            effectiveDistance *= std::cos((heading - 180) * (M_PI / 180));
            chassis.setPose(70 - effectiveDistance, pose.y, pose.theta);
            break;
        case Wall::TOP_Y:
            effectiveDistance *= std::cos((heading - 90) * (M_PI / 180));
            chassis.setPose(pose.x, 70 - effectiveDistance, pose.theta);
            break;
        case Wall::BOTTOM_Y:
            effectiveDistance *= std::cos((heading - 270) * (M_PI / 180));
            chassis.setPose(pose.x, -70 + effectiveDistance, pose.theta);
            break;
    }
}

