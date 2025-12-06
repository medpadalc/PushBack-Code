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
    // open stopes scoring
    subsystems::hood::open();
    subsystems::hood::close();

    subsystems::matchload::extend();
    subsystems::matchload::retract();
}

void solo_awp() {

    subsystems::wing::extend();
    chassis.setPose(-45, -17.5, 180);
    subsystems::hood::open();
    chassis.moveToPoint(-45, -48, 2500, {.maxSpeed = 90, .minSpeed = 5, .earlyExitRange = 0.5});
    subsystems::matchload::extend();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-55, -49, 2500, {.maxSpeed = 85, .minSpeed = 50, .earlyExitRange = 6});


    // shake in the matchloaer
    chassis.moveToPoint(-61, -50, 900, {.maxSpeed = 70, .minSpeed = 35, .earlyExitRange = 1});
    chassis.waitUntilDone();
    chassis.tank(-7,-7);
    pros::delay(200);
    chassis.tank(25,25);
    pros::delay(300);
    chassis.tank(0,0);


    chassis.moveToPoint(-25, -49.5, 2500, {.forwards = false, .maxSpeed = 100, .minSpeed = 50, .earlyExitRange = 1});
    chassis.waitUntil(17);
    chassis.cancelMotion();
    chassis.moveToPoint(-18, -49.5, 800, {.forwards = false, .maxSpeed = 55, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(5);
    subsystems::hood::close();
    subsystems::matchload::retract();

    chassis.waitUntilDone();
    pros::delay(300);
    chassis.setPose(-26, -40.5, 270);
    pros::delay(100);
    
    //chassis.swingToPoint(-23, -27 , lemlib::DriveSide::LEFT, 800, {.maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 1});
    
    chassis.turnToPoint(-32, -27, 1400, {.maxSpeed = 95, .minSpeed = 50, .earlyExitRange = 3});
    subsystems::hood::open();
    chassis.moveToPoint(-28, -18, 1200, {.maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(6);
    subsystems::matchload::extend();
    
    chassis.moveToPoint(-27, 12, 1200, {.maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 1});
    chassis.waitUntil(10);
    chassis.cancelMotion();
    subsystems::matchload::retract();
    
    chassis.moveToPoint(-25, 12, 1200, {.maxSpeed = 95, .minSpeed = 50, .earlyExitRange = 1});

    
    chassis.moveToPoint(-25, 28, 1200, {.maxSpeed = 55, .minSpeed = 30, .earlyExitRange = 1});
    chassis.waitUntil(2);
    subsystems::matchload::extend();
    
    chassis.moveToPose(-12.5, 12.5, 315, 2000, {.forwards = false, .maxSpeed = 50, .earlyExitRange = 4});
    chassis.waitUntil(23);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    chassis.moveToPose(-12.5, 12.5, 315, 400, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    
    pros::delay(100);

    
    subsystems::hood::open();
    
    chassis.moveToPoint(-40, 47.5, 2000,  {.maxSpeed = 95, .minSpeed = 20, .earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-69.5, 51, 800, {.maxSpeed = 75, .minSpeed = 40, .earlyExitRange = 6});
    subsystems::matchload::extend();

    chassis.moveToPoint(-69.5, 51.5, 1100, {.maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 2});
    chassis.waitUntilDone();
    chassis.tank(-7, -7);
    pros::delay(200);
    chassis.tank(25,25);
    pros::delay(200);
    chassis.tank(0,0);
    subsystems::hood::open();

    chassis.moveToPoint(-10, 51, 500, {.forwards = false, .maxSpeed = 100, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-10, 51, 1900, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(10);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(3000);
    



    





}

void left() {
    chassis.setPose(-42, 11 ,90 );
    subsystems::hood::open();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.moveToPoint(-30, 11, 2000, {.maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 1});
    chassis.moveToPoint(-13, 26, 2000, {.maxSpeed = 35, .minSpeed = 30});
    chassis.moveToPose(-1.25, 5.25, 315, 2500, {.forwards = false, .maxSpeed = 50});
    chassis.waitUntilDone();
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    
    pros::delay(900);

    subsystems::matchload::extend();
    subsystems::hood::open();
    
    chassis.moveToPoint(-35, 41, 2000,  {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-71, 42, 1100, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 3});

    chassis.moveToPoint(-71.5, 42, 1550, {.maxSpeed = 50, .minSpeed = 40, .earlyExitRange = 2});
    chassis.waitUntilDone();
    
    chassis.tank(-9,-9);
    pros::delay(250);
    chassis.tank(16,16);
    pros::delay(600);
    chassis.tank(0,0);
    subsystems::hood::open();

    chassis.moveToPoint(-10, 41.25, 500, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-10, 41.25, 1900, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(16);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(1000);
    chassis.setPose(-15, 42, 270);
    pros::delay(100);
    

    chassis.moveToPoint(-30, 52.5, 1300, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 2});
    chassis.moveToPose(-17, 52.5, 260, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 2});

    
    chassis.moveToPoint(-2, 52.5, 3500, {.forwards = false, .maxSpeed = 60, .minSpeed = 20});
    subsystems::wing::retract();
    chassis.waitUntilDone();
    chassis.swingToHeading(270, DriveSide::LEFT, 500, {.minSpeed = 60});

}
void right() {
    chassis.setPose(-42, -12, 90 );
    subsystems::hood::open();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.moveToPoint(-32, -12, 2000, {.maxSpeed = 75, .minSpeed = 35, .earlyExitRange = 1});
    chassis.moveToPoint(-13, -24, 2000, {.maxSpeed = 35, .minSpeed = 25});
    chassis.moveToPose(-4, -7.5, 45, 2800, { .maxSpeed = 50});
    chassis.waitUntilDone();
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);
    
    pros::delay(1800);

    
    subsystems::hood::open();
    
    chassis.moveToPoint(-35, -39, 2000,  {.forwards = false, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-59, -39.5, 800, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 5});
    subsystems::matchload::extend();
    chassis.moveToPoint(-61.5, -39.5, 850, {.maxSpeed = 67, .minSpeed = 50, .earlyExitRange = 2});
    chassis.waitUntilDone();    
    chassis.tank(-7, -7);
    pros::delay(200);
    
    chassis.tank(20,20);
    pros::delay(600);
    chassis.tank(0,0);
    subsystems::hood::open();

    chassis.moveToPoint(-10, -43, 600, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-9, -43, 1600, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(12);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.waitUntilDone();
    pros::delay(800);
    chassis.setPose(-15, -42, 270);
    pros::delay(100);
    

    chassis.moveToPoint(-30, -50, 1300, {.maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 2});
    chassis.moveToPose(-20, -52, 270, 3500, {.forwards = false, .maxSpeed = 75});

    
    chassis.moveToPoint(-5.5, -52, 3500, {.forwards = false, .maxSpeed = 80, .minSpeed = 50, .earlyExitRange = 1});
    subsystems::wing::retract();
    subsystems::matchload::retract();
    chassis.waitUntilDone();
    chassis.tank(0,0);
    //chassis.swingToHeading(270, DriveSide::LEFT, 500, {.minSpeed = 60});
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
    //score middle goal


    chassis.moveToPose(7.75, -7.75, 135, 2000, {.forwards = false, .maxSpeed = 70});
    
    chassis.waitUntilDone();
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    pros::delay(1800);
    subsystems::intake::run(subsystems::intake::GoalType::NONE);


    chassis.moveToPoint(40, -46.5, 2500, {.maxSpeed = 60, .earlyExitRange = 0.5});
    chassis.turnToPoint(69.5, -47.5, 2000, {.minSpeed = 30, .earlyExitRange = 7});
    subsystems::matchload::extend();

    chassis.moveToPoint(68, -47.5, 1500, {.maxSpeed = 60, .minSpeed = 40});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    // matchload
    chassis.waitUntilDone();
    chassis.tank(-7, -7);
    pros::delay(200);
    chassis.tank(15, 15);
    pros::delay(700);
    chassis.tank(0, 0);
    pros::delay(800);




    chassis.moveToPoint(48, -47, 2500, {.forwards = false, .maxSpeed = 60, .earlyExitRange = 0.5});
    chassis.turnToPoint(34, -59, 2500, {.forwards = false, .minSpeed = 30, .earlyExitRange = 5});

    chassis.moveToPoint(34, -59, 2500, {.forwards = false, .maxSpeed = 60, .earlyExitRange = 1});
    chassis.turnToPoint(60, -59, 1000, {.minSpeed = 30, .earlyExitRange = 3});
    chassis.moveToPoint(-35, -57, 2500, {.forwards = false, .maxSpeed = 75});
    subsystems::intake::run(subsystems::intake::GoalType::NONE);
    subsystems::matchload::retract();

    chassis.moveToPoint(-47, -46, 2500, {.forwards = false, .maxSpeed = 60});
    chassis.moveToPoint(-23, -45.1, 1400, {.forwards = false, .maxSpeed = 70});
    chassis.waitUntil(15);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);


    //score high goal
    // score first High goal
    chassis.waitUntilDone();
    
    
    chassis.tank(50, 50);
    pros::delay(100);
    chassis.tank(-127, -127);
    subsystems::hood::close();
    pros::delay(2300);

    chassis.tank(0, 0);
    pros::delay(100);
    chassis.setPose(-28, -44, 270);
    pros::delay(100);
    chassis.moveToPoint(-70.5, -41.5, 1400, {.maxSpeed = 60, .minSpeed = 30});
    subsystems::matchload::extend();
    chassis.waitUntil(8);
    subsystems::hood::open();
    chassis.waitUntilDone();
    chassis.tank(-7, -7);
    pros::delay(200);
    chassis.tank(10, 10);
    pros::delay(800);
    chassis.tank(0, 0);
    pros::delay(700);

    chassis.moveToPoint(-24, -43, 1400, {.forwards = false, .maxSpeed = 70});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.waitUntilDone();
    //second High goal score
    subsystems::matchload::retract();

    
    chassis.tank(50, 50);
    pros::delay(100);
    subsystems::hood::close();

    chassis.tank(-127, -127);
    pros::delay(2500);
    chassis.tank(0, 0);
    pros::delay(100);
    chassis.setPose(-28, -44, 270);
    pros::delay(100);
    


    //side two
    chassis.moveToPoint(-32, -44, 1000);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    
    

    chassis.turnToPoint(-23, -23, 2000, {.minSpeed = 30, .earlyExitRange = 3});
    subsystems::hood::open();
    chassis.moveToPoint(-23, -23, 2000, {.maxSpeed = 70});
    chassis.waitUntil(14);
    subsystems::matchload::extend();
    chassis.waitUntilDone();
    subsystems::matchload::retract();

    chassis.moveToPoint(-22, 23, 2000, {.maxSpeed = 80});
    chassis.waitUntil(25);
    chassis.cancelMotion();
    chassis.moveToPoint(-22, 23, 2000, {.maxSpeed = 50});


    chassis.moveToPoint(-46, 51, 2000, {.maxSpeed = 70});


    chassis.turnToPoint(-70, 51, 1000, {.earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.moveToPoint(-22, 52, 1000, {.forwards = false, .maxSpeed = 60});
    chassis.waitUntil(10);
    //score third high  goal
    //
    ///
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.waitUntilDone();
    
    chassis.tank(50, 50);
    pros::delay(100);
    subsystems::hood::close();

    chassis.tank(-127, -127);
    pros::delay(2300);

    chassis.tank(0, 0);
    pros::delay(100);
    chassis.setPose(-28, 43, chassis.getPose().theta);
    pros::delay(100);
    chassis.moveToPoint(-70.5, 44.5, 1600, {.maxSpeed = 62, .minSpeed = 45});
    subsystems::matchload::extend();
    chassis.waitUntil(8);
    subsystems::hood::open();
    chassis.waitUntilDone();
    chassis.tank(-7, -7);
    pros::delay(200);
    chassis.tank(10, 10);
    pros::delay(1000);
    chassis.tank(0, 0);
    pros::delay(300);

    
    chassis.moveToPoint(-28, 55.25, 2500, {.forwards = false, .maxSpeed = 65});

    chassis.waitUntilDone();
    chassis.waitUntil(10);
    subsystems::matchload::retract();

    subsystems::intake::run(subsystems::intake::GoalType::NONE);

    chassis.moveToPoint(32, 54, 2500, {.forwards = false, .maxSpeed = 65});

    chassis.moveToPoint(39, 43.75, 2500, {.forwards = false, .maxSpeed = 65});

    chassis.moveToPoint(21, 43, 1700, {.forwards = false, .maxSpeed = 65});

    chassis.waitUntil(15);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    //second High goal score
    
    chassis.waitUntilDone();
    
    chassis.tank(50, 50);
    pros::delay(225);
    subsystems::hood::close();
    chassis.tank(-127, -100);
    pros::delay(800);
    chassis.tank(-127, -127);
    pros::delay(1100);

    chassis.tank(0, 0);
    pros::delay(100);
    chassis.setPose(28, 44.5, chassis.getPose().theta);
    pros::delay(100);

    chassis.moveToPoint(70, 41.75, 1500, {.maxSpeed = 60, .minSpeed = 40});
    subsystems::matchload::extend();
    chassis.waitUntilDone();
    chassis.tank(-7, -7);
    pros::delay(200);
    chassis.tank(15, 15);
    pros::delay(1000);
    chassis.tank(0, 0);
    pros::delay(500);

    chassis.moveToPoint(23, 43.5, 1800, {.forwards = false, .maxSpeed = 65});

    
    subsystems::matchload::retract();
    chassis.waitUntilDone();
    
    chassis.tank(50, 50);
    pros::delay(100);
    subsystems::hood::close();
    chassis.tank(-127, -127);
    pros::delay(2000);
    chassis.tank(0, 0);
    pros::delay(100);


    // try parking
    chassis.setPose(28, 44, 90);
    pros::delay(100);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);


    chassis.moveToPoint(57, 38, 2000, {.maxSpeed = 65});    
    chassis.waitUntil(15);
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);

    chassis.moveToPoint(59, -3, 4000, {.minSpeed = 127});
    chassis.waitUntilDone();

    chassis.moveToPoint(59, -1, 200, {.forwards = false, .minSpeed = 100});
    chassis.waitUntilDone();


}
void tunePid() {
    chassis.setPose(28, 44, 90);
    pros::delay(100);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);


    chassis.moveToPoint(57, 38, 2000, {.maxSpeed = 65});    
    chassis.waitUntil(15);
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);

    chassis.moveToPoint(59, -3, 4000, {.minSpeed = 127});
    chassis.waitUntilDone();

    chassis.moveToPoint(59, -1, 200, {.forwards = false, .minSpeed = 100});
    chassis.waitUntilDone();
}
