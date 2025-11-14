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
    chassis.setPose(-56, 14,90 );
    subsystems::hood::open();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.moveToPoint(-30, 14, 2000, {.maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 1});
    chassis.moveToPoint(-13, 24, 2000, {.maxSpeed = 35, .minSpeed = 30});
    chassis.moveToPose(-4, 3, 315, 2500, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    pros::delay(1000);
    subsystems::intake::stop();
    chassis.moveToPoint(-35, 39, 2500, {.maxSpeed = 85});
    subsystems::matchload::extend();
    chassis.moveToPoint(-55, 44, 1300, {.maxSpeed = 80});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-69, 44, 700, {.maxSpeed = 45});
    chassis.waitUntilDone();
    subsystems::hood::open();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.tank(5, 5);
    pros::delay(1300);
    chassis.tank(0,0);
    chassis.moveToPoint(-34, 42.5, 2500, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 5});
    chassis.moveToPoint(-20, 42.5, 2500, {.forwards = false, .maxSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntilDone();
    subsystems::hood::close();
    //subsystems::matchload::retract();
    pros::delay(10000);
    chassis.setPose(22.5, 41.6, 270);
    chassis.moveToPoint(-30, 30, 1300, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 2});
    chassis.moveToPose(-17, 31, 260, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 2});

    
    chassis.moveToPoint(-10, 30, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 20});
    subsystems::wing::retract();
    chassis.waitUntilDone();

    


}
void right() {
}

void tunePid() {
    chassis.setPose(0,0,0);
    chassis.turnToHeading(90, 5000);
    chassis.waitUntilDone();
}
