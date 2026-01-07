#include "subsystems.hpp"

pros::Motor lowerIntakeMotor(1, pros::MotorGears::rpm_600);
pros::Motor upperIntakeMotor(-18, pros::MotorGears::rpm_600);
pros::Optical intakeOpticalSensor(11);

pros::adi::Pneumatics matchloadPiston('H',false);
pros::adi::Pneumatics middleGoalPiston('F', true, true);
pros::adi::Pneumatics wingPiston('G', false, true);
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

static constexpr int NONE = 0;
static constexpr int RED = 1;
static constexpr int BLUE = 2;

int getColor(pros::Optical& optical) {
    optical.set_integration_time(10);
    optical.set_led_pwm(100);

    double hue = intakeOpticalSensor.get_hue();
    double proximity = intakeOpticalSensor.get_proximity();

    if (proximity > 150 && (hue > 180 && hue < 260)) {
        return RED;
    }
    if (proximity > 150 && (hue > 330 || hue < 30)) {
        return BLUE;
    }
    return NONE;
}

void subsystems::intake::matchloadUntilColorChanges(std::uint32_t timeout) {
    intakeOpticalSensor.set_integration_time(10);
    intakeOpticalSensor.set_led_pwm(100);

    std::uint32_t start = pros::millis();

    int initialColor = NONE;
    while (initialColor == NONE && (pros::millis() - start) < timeout) {
        iterate(GoalType::HOLD_BALLS);
        initialColor = getColor(intakeOpticalSensor);
        pros::delay(10);
    }

    if (initialColor == NONE) {
        stop();
        return;
    }


    int currentColor = initialColor;
    while (((initialColor == RED && currentColor != BLUE) ||
           (initialColor == BLUE && currentColor != RED)) && (pros::millis() - start) < timeout) {
        iterate(GoalType::HOLD_BALLS);
        currentColor = getColor(intakeOpticalSensor);
        pros::delay(10);
    }

    stop();
}


void subsystems::intake::iterate(GoalType goalType) {
    intakeOpticalSensor.set_integration_time(10);
    intakeOpticalSensor.set_led_pwm(100);

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
            lowerIntakeMotor.move(127);
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
