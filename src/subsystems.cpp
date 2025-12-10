#include "subsystems.hpp"

pros::MotorGroup mainIntakeMotor({-9, 10});
pros::Motor endIntakeMotor(20, pros::MotorGears::rpm_200);
pros::Optical intakeOpticalSensor(18);

pros::adi::Pneumatics matchloadPiston('H',false);
pros::adi::Pneumatics hoodPiston('D', false);
pros::adi::Pneumatics wingPiston('E', false);

std::shared_ptr<pros::Task> intakingTaskPtr = nullptr;
subsystems::intake::AllianceColor currentAllianceColor = subsystems::intake::AllianceColor::DISABLED;

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
    intakeOpticalSensor.set_integration_time(10);
    intakeOpticalSensor.set_led_pwm(100);

    static bool isSorting = false;
    static int32_t startedSorting = pros::millis();

    switch (goalType) {
        case GoalType::NONE:
            mainIntakeMotor.brake();
            endIntakeMotor.brake();
            break;
        case GoalType::LOW_GOAL:
            mainIntakeMotor.move(-127);
            endIntakeMotor.move(0);
            break;
        case GoalType::MEDIUM_GOAL:
            mainIntakeMotor.move(127);
            endIntakeMotor.move(-127);
            break;
        case GoalType::MEDIUM_GOAL_SLOW:
            mainIntakeMotor.move(127);
            endIntakeMotor.move_velocity(-80);
            break;
        case GoalType::LONG_GOAL:
            mainIntakeMotor.move(127);
            double hue = intakeOpticalSensor.get_hue();
            if (
                    intakeOpticalSensor.get_proximity() > 200 &&
                    ((currentAllianceColor == AllianceColor::RED && hue > 180 && hue < 260) ||
                    (currentAllianceColor == AllianceColor::BLUE && (hue > 330 || hue < 30)))
                ) {
                isSorting = true;
                startedSorting = pros::millis();
            }    

            if (pros::millis() - startedSorting > 20) {
                isSorting = false;
            }

            if (isSorting) {
                endIntakeMotor.move(-127);
            } else {
                endIntakeMotor.move(127);
            }
            break;
    }
}

void subsystems::intake::stop() {
    if (intakingTaskPtr) {
        intakingTaskPtr->remove();
        intakingTaskPtr = nullptr;
    }

    mainIntakeMotor.brake();
    endIntakeMotor.brake();
}

std::string subsystems::intake::getAllianceColorAsString() {
    if (currentAllianceColor == AllianceColor::RED) {
        return "R";
    }
    if (currentAllianceColor == AllianceColor::BLUE) {
        return "B";
    }
    if (currentAllianceColor == AllianceColor::DISABLED) {
        return "D";
    }
    std::unreachable();
}

void subsystems::intake::setAllianceColor(AllianceColor color) {
    currentAllianceColor = color;
}

void subsystems::intake::toggleAllianceColor() {
    if (currentAllianceColor == AllianceColor::RED || currentAllianceColor == AllianceColor::DISABLED) {
        setAllianceColor(AllianceColor::BLUE);
    } else {
        setAllianceColor(AllianceColor::RED);
    }
}

void subsystems::intake::disableColorSort() {
    setAllianceColor(AllianceColor::DISABLED);
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

