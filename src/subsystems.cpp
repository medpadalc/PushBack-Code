#include "subsystems.hpp"

pros::MotorGroup mainIntakeMotor({9, -10});
pros::Motor endIntakeMotor(20);
pros::Optical intakeOpticalSensor(7);

pros::adi::Pneumatics matchloadPiston('G',false);
pros::adi::Pneumatics hoodPiston('B', false);
pros::adi::Pneumatics wingPiston('H', false);

std::shared_ptr<pros::Task> intakingTaskPtr = nullptr;
subsystems::intake::AllianceColor currentAllianceColor = subsystems::intake::AllianceColor::RED;

void subsystems::intake::run(GoalType goalType) {
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
            mainIntakeMotor.brake();
            endIntakeMotor.brake();
        case GoalType::LOW_GOAL:
            mainIntakeMotor.move(-127);
            endIntakeMotor.move(-127);
            break;
        case GoalType::MEDIUM_GOAL:
            mainIntakeMotor.move(127);
            endIntakeMotor.move(-127);
            break;
        case GoalType::LONG_GOAL:
            mainIntakeMotor.move(127);
            double hue = intakeOpticalSensor.get_hue();
            if (
                    intakeOpticalSensor.get_proximity() > 200 &&
                    ((currentAllianceColor == AllianceColor::BLUE && hue > 200 && hue < 260) ||
                    (currentAllianceColor == AllianceColor::RED && (hue > 330 || hue < 30)))
                ) {
                endIntakeMotor.move(-127);
            } else {
                endIntakeMotor.move(127);
            }
    }
}

void subsystems::intake::stop() {
    intakingTaskPtr->remove();
    intakingTaskPtr = nullptr;
}

void subsystems::intake::setAllianceColor(AllianceColor color) {
    currentAllianceColor = color;
}

void subsystems::hood::open() {
    hoodPiston.extend();
}

void subsystems::hood::close() {
    hoodPiston.retract();
}

void subsystems::hood::toggle() {
    hoodPiston.toggle();
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

