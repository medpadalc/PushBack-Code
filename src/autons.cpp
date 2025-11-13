#include "autons.hpp"

void example() {
    // long goal
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(1000);
    subsystems::intake::stop();

    // medium goal
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    pros::delay(1000);
    subsystems::intake::stop();

    // low goal
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);
    pros::delay(1000);
    subsystems::intake::stop();

    subsystems::hood::open();
    subsystems::hood::close();

    subsystems::matchload::extend();
    subsystems::matchload::retract();
}

void solo_awp() {
}

void left() {
}

void right() {
}

void tunePid() {
}
