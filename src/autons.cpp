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
    chassis.setPose(-45, -11.5, 180);
    subsystems::hood::open();
    chassis.moveToPoint(-45, -46, 2500, {.maxSpeed = 80});
    subsystems::matchload::extend();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-55, -49, 2500, {.maxSpeed = 80, .earlyExitRange = 1});

    chassis.moveToPoint(-57, -49, 1900, {.maxSpeed = 80, .earlyExitRange = 1});
    chassis.moveToPoint(-60, -49, 600, {.maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntilDone();
    chassis.tank(25,25);
    pros::delay(100);
    chassis.tank(0,0);


    chassis.moveToPoint(-25, -49.5, 2500, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(17);
    chassis.cancelMotion();
    chassis.moveToPoint(-20, -49.5, 1100, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(15);
    subsystems::hood::close();
    subsystems::matchload::retract();

    chassis.waitUntilDone();
    pros::delay(300);
    chassis.setPose(-26, -48, 270);
    pros::delay(100);
    
    //chassis.swingToPoint(-23, -27 , lemlib::DriveSide::LEFT, 800, {.maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 1});
    
    chassis.turnToPoint(-26, -27, 1400, {.maxSpeed = 95, .minSpeed = 50, .earlyExitRange = 1});
    subsystems::hood::open();
    chassis.moveToPoint(-25, -18, 1200, {.maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(6);
    subsystems::matchload::extend();
    
    chassis.moveToPoint(-26, 12, 1200, {.maxSpeed = 95, .minSpeed = 50, .earlyExitRange = 1});
    chassis.waitUntil(10);
    chassis.cancelMotion();
    subsystems::matchload::retract();
    
    chassis.moveToPoint(-25, 12, 1200, {.maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 1});

    
    chassis.moveToPoint(-25, 28, 1200, {.maxSpeed = 55, .minSpeed = 30, .earlyExitRange = 1});
    chassis.waitUntil(2);
    subsystems::matchload::extend();
    
    chassis.moveToPose(-7.25, 9, 315, 2000, {.forwards = false, .maxSpeed = 50, .earlyExitRange = 4});
    chassis.waitUntil(23);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    chassis.moveToPose(-7.25, 9, 315, 400, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    
    pros::delay(100);

    
    subsystems::matchload::extend();
    subsystems::hood::open();
    
    chassis.moveToPoint(-40, 48, 2000,  {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-67, 54.5, 800, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 5});

    chassis.moveToPoint(-67, 54.5, 1200, {.maxSpeed = 50, .minSpeed = 40, .earlyExitRange = 2});
    chassis.waitUntilDone();
    
    chassis.tank(25,25);
    pros::delay(300);
    chassis.tank(0,0);
    subsystems::hood::open();

    chassis.moveToPoint(-10, 55, 500, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-10, 55, 1900, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(10);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(1500);
    



    





}

void left() {
    chassis.setPose(-42, 18 ,90 );
    subsystems::hood::open();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.moveToPoint(-30, 17, 2000, {.maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 1});
    chassis.moveToPoint(-13, 26, 2000, {.maxSpeed = 35, .minSpeed = 30});
    chassis.moveToPose(-6.2, 1.8, 315, 2500, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    
    pros::delay(900);

    subsystems::matchload::extend();
    subsystems::hood::open();
    
    chassis.moveToPoint(-40, 41, 2000,  {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-71, 42, 1100, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 3});

    chassis.moveToPoint(-72, 42, 1550, {.maxSpeed = 45, .minSpeed = 40, .earlyExitRange = 2});
    chassis.waitUntilDone();
    
    chassis.tank(16,16);
    pros::delay(600);
    chassis.tank(0,0);
    subsystems::hood::open();

    chassis.moveToPoint(-10, 42, 500, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-10, 42, 1900, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(20);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(1500);
    chassis.setPose(-15, 42, 270);
    pros::delay(100);
    

    chassis.moveToPoint(-30, 30.5, 1300, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 2});
    chassis.moveToPose(-17, 31.5, 260, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 2});

    
    chassis.moveToPoint(-2, 30.5, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 20});
    subsystems::wing::retract();
    chassis.waitUntilDone();
    chassis.swingToHeading(270, DriveSide::LEFT, 500, {.minSpeed = 60});

}
void right() {
    chassis.setPose(-42, -8, 90 );
    subsystems::hood::open();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.moveToPoint(-32, -8, 2000, {.maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 1});
    chassis.moveToPoint(-13, -24, 2000, {.maxSpeed = 30, .minSpeed = 20});
    chassis.moveToPose(-1, -4.5, 45, 2800, { .maxSpeed = 50});
    chassis.waitUntilDone();
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);
    
    pros::delay(1800);

    
    subsystems::hood::open();
    
    chassis.moveToPoint(-38, -42, 2000,  {.forwards = false, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-59, -43, 800, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 5});
    subsystems::matchload::extend();
    chassis.moveToPoint(-59, -43, 700, {.maxSpeed = 40, .minSpeed = 40, .earlyExitRange = 2});
    chassis.waitUntilDone();
    
    chassis.tank(20,20);
    pros::delay(1200);
    chassis.tank(0,0);
    subsystems::hood::open();

    chassis.moveToPoint(-10, -48, 500, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-10, -48, 1900, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(18);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(1500);
    chassis.setPose(-15, 42, 270);
    pros::delay(100);
    

    chassis.moveToPoint(-30, 31, 1300, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 2});
    chassis.moveToPose(-17, 32, 260, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 2});

    
    chassis.moveToPoint(-2, 31, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 20});
    subsystems::wing::retract();
    chassis.waitUntilDone();
    chassis.swingToHeading(270, DriveSide::LEFT, 500, {.minSpeed = 60});
}
void skills(){
    subsystems::wing::toggle();
    subsystems::hood::open();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.setPose(49, -15, 270);
    chassis.moveToPoint(40, -15, 2000, {.maxSpeed = 60});
    chassis.moveToPoint(23, -24, 2000, {.maxSpeed = 40});
    chassis.waitUntil(15);
    subsystems::matchload::extend();
    chassis.waitUntilDone();
    
    pros::delay(300);
    chassis.turnToHeading(135, 1000, {.maxSpeed = 60});
    subsystems::matchload::retract();

    chassis.moveToPose(7, -7, 135, 2000, {.forwards = false, .maxSpeed = 70});
    
    chassis.waitUntilDone();
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    pros::delay(1800);
    subsystems::intake::run(subsystems::intake::GoalType::NONE);


    chassis.moveToPoint(44, -46, 2500, {.maxSpeed = 60, .earlyExitRange = 0.5});
    chassis.turnToPoint(68, -46, 2000, {.earlyExitRange = 7});
    subsystems::matchload::extend();

    chassis.moveToPoint(66.5, -47, 2000, {.maxSpeed = 65, .minSpeed = 15});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    // matchload
    chassis.waitUntilDone();
    chassis.tank(-7, -7);
    pros::delay(200);
    chassis.tank(15, 15);
    pros::delay(500);
    chassis.tank(0, 0);
    pros::delay(500);




    chassis.moveToPoint(48, -47, 2500, {.forwards = false, .maxSpeed = 60, .earlyExitRange = 0.5});
    chassis.turnToPoint(34, -59, 2500, {.forwards = false, .minSpeed = 30, .earlyExitRange = 5});

    chassis.moveToPoint(34, -59, 2500, {.forwards = false, .maxSpeed = 60, .earlyExitRange = 1});
    chassis.turnToPoint(60, -59, 1000, {.minSpeed = 30, .earlyExitRange = 3});
    chassis.moveToPoint(-38, -57.25, 2500, {.forwards = false, .maxSpeed = 60});
    subsystems::intake::run(subsystems::intake::GoalType::NONE);
    subsystems::matchload::retract();

    chassis.moveToPoint(-47, -46, 2500, {.forwards = false, .maxSpeed = 60});
    chassis.moveToPoint(-23, -45.1, 1700, {.forwards = false, .maxSpeed = 70});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);


    //score high goal
    chassis.waitUntilDone();
    subsystems::hood::close();
    
    chassis.tank(50, 50);
    pros::delay(100);
    chassis.tank(-127, -127);
    pros::delay(1600);

    chassis.tank(0, 0);
    pros::delay(100);
    chassis.setPose(-28, -44, 270);
    pros::delay(100);
    chassis.moveToPoint(-71, -42, 2000, {.maxSpeed = 65});
    subsystems::matchload::extend();

    subsystems::hood::open();
    chassis.waitUntilDone();
    chassis.tank(-5, -5);
    pros::delay(500);
    chassis.tank(5, 5);
    pros::delay(500);
    chassis.tank(0, 0);
    pros::delay(500);

    chassis.moveToPoint(-24, -43, 1700, {.forwards = false, .maxSpeed = 65});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.waitUntilDone();
    //second High goal score
    subsystems::hood::close();
    subsystems::matchload::retract();

    
    chassis.tank(50, 50);
    pros::delay(100);
    chassis.tank(-127, -127);
    pros::delay(1600);
    chassis.tank(0, 0);
    pros::delay(100);
    chassis.setPose(-28, -44, 270);
    pros::delay(100);
    subsystems::intake::run(subsystems::intake::GoalType::NONE);


    //side two
    chassis.moveToPoint(-32, -44, 1000);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    subsystems::hood::open();

    chassis.turnToPoint(-23, -23, 2000, {.minSpeed = 30, .earlyExitRange = 3});
    chassis.moveToPoint(-23, -23, 2000, {.maxSpeed = 80});
    chassis.waitUntil(20);
    subsystems::matchload::extend();
    chassis.waitUntilDone();
    subsystems::matchload::retract();

    chassis.moveToPoint(-23, 23, 2000, {.maxSpeed = 80});
    chassis.waitUntilDone();

    chassis.moveToPoint(-46, 51, 2000, {.maxSpeed = 80});

    chassis.turnToPoint(-70, 51, 1000, {.earlyExitRange = 1});

    chassis.moveToPoint(-22, 52, 1700, {.forwards = false, .maxSpeed = 60});

    //score third high  goal
    //
    ///
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.waitUntilDone();
    subsystems::hood::close();
    
    chassis.tank(50, 50);
    pros::delay(100);
    chassis.tank(-127, -127);
    pros::delay(1600);

    chassis.tank(0, 0);
    pros::delay(100);
    chassis.setPose(-28, 43, 270);
    pros::delay(100);
    chassis.moveToPoint(-70, 44.5, 2000, {.maxSpeed = 60});
    subsystems::matchload::extend();

    subsystems::hood::open();
    chassis.waitUntilDone();
    pros::delay(1000);

    
    chassis.moveToPoint(-28, 55.5, 2500, {.forwards = false, .maxSpeed = 65});

    chassis.waitUntilDone();
    chassis.waitUntil(10);
    subsystems::matchload::retract();

    subsystems::intake::run(subsystems::intake::GoalType::NONE);

    chassis.moveToPoint(35, 55, 2500, {.forwards = false, .maxSpeed = 65});

    chassis.moveToPoint(39, 43.5, 2500, {.forwards = false, .maxSpeed = 65});

    chassis.moveToPoint(21, 43.5, 2500, {.forwards = false, .maxSpeed = 65});

    chassis.waitUntil(15);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    //second High goal score
    subsystems::hood::close();
    chassis.waitUntilDone();
    
    chassis.tank(50, 50);
    pros::delay(100);
    chassis.tank(-127, -127);
    pros::delay(1600);
    chassis.tank(0, 0);
    pros::delay(100);
    chassis.setPose(28, 44.5, 90);
    pros::delay(100);

    chassis.moveToPoint(70, 41.5, 2000, {.maxSpeed = 65});
    subsystems::matchload::extend();
    chassis.waitUntilDone();
    pros::delay(600);

    chassis.moveToPoint(23, 43, 2500, {.forwards = false, .maxSpeed = 65});

    subsystems::hood::close();
    subsystems::matchload::retract();
    chassis.waitUntilDone();
    
    chassis.tank(50, 50);
    pros::delay(100);
    chassis.tank(-127, -127);
    pros::delay(1600);
    chassis.tank(0, 0);
    pros::delay(100);
    chassis.setPose(28, 44, 90);
    pros::delay(100);
    subsystems::intake::run(subsystems::intake::GoalType::NONE);


    chassis.moveToPoint(61, 31, 2000, {.maxSpeed = 65});    

    chassis.moveToPoint(62, -7, 2000, {.minSpeed = 100});
    chassis.waitUntilDone();









    









}
void tunePid() {
    chassis.setPose(0,0,0);
    chassis.turnToHeading(90, 5000);
    chassis.waitUntilDone();
}
