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

    subsystems::wing::extend();
    chassis.setPose(-45, -15.5, 180);
    subsystems::hood::open();
    chassis.moveToPoint(-45, -46, 2500, {.maxSpeed = 80});
    subsystems::matchload::extend();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-55, -49, 2500, {.maxSpeed = 80, .earlyExitRange = 1});

    chassis.moveToPoint(-55, -49, 1900, {.maxSpeed = 80, .earlyExitRange = 1});
    chassis.moveToPoint(-59, -49, 500, {.maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntilDone();
    chassis.tank(25,25);
    pros::delay(100);
    chassis.tank(0,0);


    chassis.moveToPoint(-25, -49, 2500, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(17);
    chassis.cancelMotion();
    chassis.moveToPoint(-22, -49, 1000, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(15);
    subsystems::hood::close();
    subsystems::matchload::retract();

    chassis.waitUntilDone();
    pros::delay(300);
    chassis.setPose(-26, -48, 270);
    pros::delay(100);
    
    //chassis.swingToPoint(-23, -27 , lemlib::DriveSide::LEFT, 800, {.maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 1});
    
    chassis.turnToPoint(-23, -27, 1400, {.maxSpeed = 95, .minSpeed = 50, .earlyExitRange = 1});
    subsystems::hood::open();
    chassis.moveToPoint(-20, -18, 1200, {.maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(6);
    subsystems::matchload::extend();
    
    chassis.moveToPoint(-19, 12, 1200, {.maxSpeed = 95, .minSpeed = 50, .earlyExitRange = 1});
    chassis.waitUntil(10);
    chassis.cancelMotion();
    subsystems::matchload::retract();
    
    chassis.moveToPoint(-19, 12, 1200, {.maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 1});

    
    chassis.moveToPoint(-19, 28, 1200, {.maxSpeed = 55, .minSpeed = 30, .earlyExitRange = 1});
    chassis.waitUntil(2);
    subsystems::matchload::extend();
    
    chassis.moveToPose(-6.25, 7.75, 315, 2500, {.forwards = false, .maxSpeed = 50, .earlyExitRange = 4});
    chassis.waitUntil(23);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    chassis.moveToPose(-6.5, 7.5, 315, 2500, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    
    pros::delay(100);

    
    subsystems::matchload::extend();
    subsystems::hood::open();
    
    chassis.moveToPoint(-40, 45, 2000,  {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-67, 48, 800, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 5});

    chassis.moveToPoint(-67, 48, 1200, {.maxSpeed = 40, .minSpeed = 40, .earlyExitRange = 2});
    chassis.waitUntilDone();
    
    chassis.tank(25,25);
    pros::delay(600);
    chassis.tank(0,0);
    subsystems::hood::open();

    chassis.moveToPoint(-10, 47, 500, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-10, 47, 1900, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(10);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(1500);
    



    





}

void left() {
    chassis.setPose(-42, 14,90 );
    subsystems::hood::open();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.moveToPoint(-30, 14, 2000, {.maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 1});
    chassis.moveToPoint(-13, 24, 2000, {.maxSpeed = 35, .minSpeed = 30});
    chassis.moveToPose(-4, 3, 315, 2500, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    
    pros::delay(900);

    subsystems::matchload::extend();
    subsystems::hood::open();
    
    chassis.moveToPoint(-40, 42, 2000,  {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-67, 43, 800, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 5});

    chassis.moveToPoint(-67, 43, 1200, {.maxSpeed = 40, .minSpeed = 40, .earlyExitRange = 2});
    chassis.waitUntilDone();
    
    chassis.tank(25,25);
    pros::delay(600);
    chassis.tank(0,0);
    subsystems::hood::open();

    chassis.moveToPoint(-10, 43, 500, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-10, 43, 1900, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(10);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(1500);
    chassis.setPose(-15, 42, 270);
    pros::delay(100);
    

    chassis.moveToPoint(-30, 31, 1300, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 2});
    chassis.moveToPose(-17, 32, 260, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 2});

    
    chassis.moveToPoint(-5, 31, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 20});
    subsystems::wing::retract();
    chassis.waitUntilDone();
    chassis.swingToHeading(270, DriveSide::LEFT, 500, {.minSpeed = 60});

}
void right() {
    chassis.setPose(-42, -14, 90 );
    subsystems::hood::open();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.moveToPoint(-30, -14, 2000, {.maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 1});
    chassis.moveToPoint(-13, -24, 2000, {.maxSpeed = 35, .minSpeed = 30});
    chassis.moveToPose(-4, 3, -45, 2500, { .maxSpeed = 50});
    chassis.waitUntilDone();
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);
    
    pros::delay(900);

    
    subsystems::hood::open();
    
    chassis.moveToPoint(-40, -42, 2000,  {.forwards = false, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-67, -43, 800, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 5});
    subsystems::matchload::extend();
    chassis.moveToPoint(-67, -43, 1200, {.maxSpeed = 40, .minSpeed = 40, .earlyExitRange = 2});
    chassis.waitUntilDone();
    
    chassis.tank(25,25);
    pros::delay(600);
    chassis.tank(0,0);
    subsystems::hood::open();

    chassis.moveToPoint(-10, -43, 500, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-10, -43, 1900, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(10);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(1500);
    chassis.setPose(-15, 42, 270);
    pros::delay(100);
    

    chassis.moveToPoint(-30, 31, 1300, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 2});
    chassis.moveToPose(-17, 32, 260, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 2});

    
    chassis.moveToPoint(-5, 31, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 20});
    subsystems::wing::retract();
    chassis.waitUntilDone();
    chassis.swingToHeading(270, DriveSide::LEFT, 500, {.minSpeed = 60});
}

void tunePid() {
    chassis.setPose(0,0,0);
    chassis.turnToHeading(90, 5000);
    chassis.waitUntilDone();
}
