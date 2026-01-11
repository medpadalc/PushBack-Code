#include "autons.hpp"

void example() {/*
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
    */
}

void solo_awp() {
    
    subsystems::wing::extend();
    chassis.setPose(-45, -17.5, 180);
    chassis.moveToPoint(-45, -46.8, 2500, {.maxSpeed = 90, .minSpeed = 5, .earlyExitRange = 0.5});
    subsystems::matchload::extend();
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);
    chassis.turnToPoint(-62, -49, 2500, {.maxSpeed = 85, .earlyExitRange = 2});


    // shake in the matchloaer
    chassis.moveToPoint(-68, -50, 950, {.maxSpeed = 80, .minSpeed = 65, .earlyExitRange = 1});
    chassis.waitUntilDone();
    chassis.tank(-7,-7);
    pros::delay(100);
    chassis.tank(60,60);
    pros::delay(350);
    chassis.tank(0,0);


    chassis.moveToPoint(-33, -49.75, 1900, {.forwards = false, .maxSpeed = 100, .minSpeed = 50, .earlyExitRange = 1});
    chassis.waitUntil(17);
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);
    pros::delay(100);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.cancelMotion();

    subsystems::matchload::retract();


    
    chassis.tank(-100, -100);

    pros::delay(1100);

    chassis.setPose(-31, -41, chassis.getPose().theta);
    pros::delay(50);
    //chassis.swingToPoint(-23, -27 , lemlib::DriveSide::LEFT, 800, {.maxSpeed = 90, .minSpeed = 50, .earlyExitRange = 1});
    chassis.moveToPoint(-39, -39, 1000);
    chassis.turnToPoint(-28, -15, 1000, {.maxSpeed = 95, .minSpeed = 50, .earlyExitRange = 3});
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);
    chassis.moveToPoint(-28, -15, 1200, {.maxSpeed = 60, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(10);
    subsystems::matchload::extend();
    
    chassis.moveToPoint(-27, 12, 1200, {.maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 1});
    chassis.waitUntil(10);
    chassis.cancelMotion();
    subsystems::matchload::retract();
    
    chassis.moveToPoint(-26.5, 12, 1200, {.maxSpeed = 95, .minSpeed = 50, .earlyExitRange = 1});

    
    chassis.moveToPoint(-27, 26, 1200, {.maxSpeed = 55, .minSpeed = 30, .earlyExitRange = 1});
    chassis.waitUntil(4);
    subsystems::matchload::extend();
    
    chassis.moveToPose(-13, 12, 315, 1500, {.forwards = false, .maxSpeed = 50, .earlyExitRange = 4});
    chassis.waitUntil(10.5);
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);
    pros::delay(75);

    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);

    chassis.waitUntilDone();
    pros::delay(600);
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);
    subsystems::matchload::retract();

    pros::delay(50);
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);


    
    
    chassis.moveToPoint(-43, 47, 2000,  {.maxSpeed = 95, .minSpeed = 20, .earlyExitRange = 1});
    chassis.turnToPoint(-70, 49.35, 800, {.maxSpeed = 75, .minSpeed = 40, .earlyExitRange = 6});
    subsystems::matchload::extend();

    chassis.moveToPoint(-71.5, 49.35, 1000, {.maxSpeed = 55, .minSpeed = 40, .earlyExitRange = 2});
    chassis.waitUntilDone();
    chassis.tank(-7, -7);
    pros::delay(100);
    chassis.tank(50,50);
    pros::delay(300);
    chassis.tank(-25,-25);
    pros::delay(100);
    chassis.tank(0,0);  
    
    chassis.moveToPoint(-10, 51.75, 600, {.forwards = false, .maxSpeed = 100, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.moveToPoint(-10, 51.25, 1900, {.forwards = false, .maxSpeed = 70, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(8);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(3000);
    
}

void left() {
    chassis.setPose(-42, 14 ,90 );
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);
    chassis.moveToPoint(-15, 19, 4000, {.maxSpeed = 110, .minSpeed = 90, .earlyExitRange = 1});
    chassis.waitUntil(15);
    subsystems::matchload::extend();
    chassis.moveToPose(-1, 4, 315, 2500, {.forwards = false, .maxSpeed = 65, .minSpeed = 30});
    chassis.waitUntil(12);
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);
    chassis.waitUntilDone();
    pros::delay(400);    
    

    subsystems::intake::stop();
    
    chassis.moveToPoint(-35, 41.25, 2000,  {.maxSpeed = 110, .minSpeed = 60, .earlyExitRange = 1.5});
    chassis.waitUntil(5);
    subsystems::matchload::retract();
    chassis.waitUntil(8);
    subsystems::matchload::extend();




    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);
    chassis.turnToPoint(-71, 42.25, 1100, {.maxSpeed = 100, .minSpeed = 70, .earlyExitRange = 3});

    chassis.moveToPoint(-76, 42.25, 1200, {.maxSpeed = 60, .minSpeed = 45, .earlyExitRange = 1});
    chassis.waitUntilDone();

    chassis.tank(75, 75);
    pros::delay(100);



    chassis.moveToPoint(-10, 42.5, 500, {.forwards = false, .maxSpeed = 100, .minSpeed = 70, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-10, 42.5, 1000, {.forwards = false, .maxSpeed = 90, .minSpeed = 55, .earlyExitRange = 1});
    chassis.waitUntil(10);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    subsystems::matchload::retract();

    chassis.waitUntilDone();
    chassis.tank(-80, -80);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    pros::delay(500);
    chassis.tank(0,0);
    pros::delay(200);
    chassis.setPose(-15, -42, 270);
    pros::delay(100);
    

    chassis.moveToPoint(-30, -50.55, 1300, {.maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 2});
    chassis.moveToPose(-20, -51.55, 270, 3500, {.forwards = false, .maxSpeed = 75, .minSpeed = 30, .earlyExitRange = 1});

    
    chassis.moveToPoint(-5, -51.55, 4000, {.forwards = false, .maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 1});
    subsystems::wing::retract();
    subsystems::matchload::retract();
    chassis.waitUntilDone();
    chassis.swingToHeading(270, lemlib::DriveSide::LEFT, 1000);
    chassis.tank(30,0);
    pros::delay(10000000);
}
void right() {
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);
    chassis.setPose(-42, -12, 90 );
    chassis.moveToPoint(-25, -16, 4000, {.maxSpeed = 80, .minSpeed = 30, .earlyExitRange = 1});
    chassis.waitUntil(16);
    subsystems::matchload::extend();
    chassis.waitUntilDone();
    
    pros::delay(500);

    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);

    chassis.moveToPoint(-42, -43.25, 2000,  {.maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 1});
    chassis.waitUntil(5);
    subsystems::matchload::retract();
    chassis.waitUntil(15);
    subsystems::matchload::extend();
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);
    
    chassis.turnToPoint(-71, -43, 1100, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 3});

    chassis.moveToPoint(-71.5, -43, 1000, {.maxSpeed = 50, .minSpeed = 40, .earlyExitRange = 2});
    


    chassis.waitUntilDone();

    chassis.tank(10, 10);
    pros::delay(150);

    chassis.moveToPoint(-10, -43, 500, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);

    chassis.cancelMotion();
    chassis.moveToPoint(-10, -43, 1000, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(10);

    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);
    pros::delay(150);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.waitUntilDone();
    subsystems::matchload::retract();

    pros::delay(1800);
    subsystems::matchload::retract();

    chassis.setPose(-15, -42, 270);
    pros::delay(100);

    
    chassis.moveToPoint(-30, -50, 1300, {.maxSpeed = 100, .minSpeed = 40, .earlyExitRange = 2});
    chassis.moveToPose(-20, -51.5, 270, 3500, {.forwards = false, .maxSpeed = 100});
    subsystems::wing::retract();


    chassis.moveToPoint(-12.55, -51.5, 3500, {.forwards = false, .minSpeed = 80});
    subsystems::matchload::retract();
    chassis.waitUntilDone();
    chassis.swingToHeading(270, lemlib::DriveSide::LEFT, 1500, {.minSpeed = 100});
    chassis.tank(0,0);
    pros::delay(100000);

    /*
    subsystems::hood::open();
    
    chassis.moveToPoint(-35, -39, 2000,  {.forwards = false, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.turnToPoint(-59, -39.5, 800, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 5});
    subsystems::matchload::extend();
    chassis.moveToPoint(-61.5, -39.5, 850, {.maxSpeed = 67, .minSpeed = 50, .earlyExitRange = 2});
    chassis.waitUntilDone();    
    chassis.tank(-12, -12);
    pros::delay(200);
    
    chassis.tank(30, 30);
    pros::delay(600);
    chassis.tank(-7, -7);
    pros::delay(100);
    chassis.tank(7, 7);
    pros::delay(100);
    chassis.tank(0,0);
    subsystems::hood::open();
    subsystems::intake::stop();

    chassis.moveToPoint(-10, -43, 600, {.forwards = false, .maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(15);
    chassis.cancelMotion();
    chassis.moveToPoint(-9, -43, 1600, {.forwards = false, .maxSpeed = 40, .minSpeed = 25, .earlyExitRange = 1});
    chassis.waitUntil(12);
    subsystems::hood::close();
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.waitUntilDone();
    pros::delay(600);
    chassis.setPose(-15, -42, 270);
    pros::delay(100);
    

    chassis.moveToPoint(-30, -50, 1300, {.maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 2});
    chassis.moveToPose(-20, -52, 270, 1000, {.forwards = false, .maxSpeed = 75});

    
    chassis.moveToPoint(-6.5, -52, 3500, {.forwards = false, .maxSpeed = 80, .minSpeed = 50, .earlyExitRange = 1});
    subsystems::wing::retract();
    subsystems::matchload::retract();
    chassis.waitUntilDone();
    chassis.tank(0,0);
    //chassis.swingToHeading(270, DriveSide::LEFT, 500, {.minSpeed = 60});
    */
}

void skills(){
    
    subsystems::wing::toggle();
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);
    chassis.setPose(49, -17, 270);
    chassis.moveToPoint(40, -15.5, 2000, {.maxSpeed = 75});
    chassis.moveToPoint(22.5, -24.5, 2000, {.maxSpeed = 55});
    chassis.waitUntil(15);
    subsystems::matchload::extend();
    chassis.waitUntilDone();
    
    pros::delay(300);
    chassis.turnToHeading(135, 1000, {.maxSpeed = 70, .minSpeed = 30});
    //score middle goal


    chassis.moveToPose(7.75, -7.75, 135, 2000, {.forwards = false, .maxSpeed = 70});
    chassis.waitUntil(15);
    subsystems::intake::run(subsystems::intake::GoalType::MEDIUM_GOAL);

    chassis.waitUntilDone();
    pros::delay(1000);
    chassis.moveToPoint(40, -45, 2500, {.maxSpeed = 75, .earlyExitRange = 0.5});
    chassis.turnToPoint(68, -48, 2000, {.minSpeed = 30, .earlyExitRange = 7});

    subsystems::intake::run(subsystems::intake::GoalType::NONE);


    


    chassis.moveToPoint(70.5, -47, 1550, {.maxSpeed = 55, .minSpeed = 40});
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);
    // matchload 1
    chassis.waitUntilDone();
    chassis.tank(-7, -7);
    pros::delay(200);
    chassis.tank(20, 20);
    pros::delay(650);
    chassis.tank(20, 20);
    pros::delay(200);
    chassis.tank(-20, -20);
    pros::delay(150);
    chassis.tank(35, 35);
    pros::delay(1000);

    chassis.moveToPoint(48, -47, 2500, {.forwards = false, .maxSpeed = 60, .earlyExitRange = 0.5});
    chassis.turnToPoint(34, -59, 2500, {.forwards = false, .minSpeed = 30, .earlyExitRange = 5});

    chassis.moveToPoint(34, -59, 2500, {.forwards = false, .maxSpeed = 60, .earlyExitRange = 1});
    chassis.turnToPoint(60, -59, 1000, {.minSpeed = 30, .earlyExitRange = 3});
    chassis.moveToPoint(-35, -57, 2500, {.forwards = false, .maxSpeed = 95});
    subsystems::matchload::retract();

    chassis.moveToPoint(-47, -46, 2500, {.forwards = false, .maxSpeed = 85});
    chassis.moveToPoint(-23, -45.75, 1400, {.forwards = false, .maxSpeed = 70});
    chassis.waitUntil(15);


    //score high goal
    // score first High goal
    chassis.waitUntilDone();
    
    
    chassis.tank(50, 50);
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);

    pros::delay(100);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.tank(-127, -127);
    subsystems::matchload::extend();
    pros::delay(2300);
    chassis.setPose(-28, -44, 270);
    pros::delay(50);

    chassis.tank(0, 0);
    pros::delay(100);
    
    pros::delay(100);

    chassis.moveToPoint(-72.5, -44.25, 1400, {.maxSpeed = 52, .minSpeed = 40});

    chassis.waitUntil(5);
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);

    //matchload 2
    chassis.waitUntilDone();
    chassis.tank(-15, -15);
    pros::delay(200);
    chassis.tank(25, 25);
    pros::delay(1000);
    chassis.tank(-4, -4);
    pros::delay(100);
    chassis.tank(20, 20);
    pros::delay(800);

    chassis.tank(0, 0);
    pros::delay(200);



    chassis.moveToPoint(-24, -44, 1400, {.forwards = false, .maxSpeed = 70});
    

    chassis.waitUntilDone();
    //second High goal score
    subsystems::matchload::retract();

    
    chassis.tank(50, 50);
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);

    pros::delay(100);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.tank(-127, -127);
    pros::delay(2500);
    
    chassis.setPose(-28, -44, 270);
    pros::delay(150);
    chassis.tank(0, 0);
    


    //side two
    chassis.moveToPoint(-35, -44, 1000);
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);
    
    

    chassis.turnToPoint(-29.5, -23, 2000, {.minSpeed = 30, .earlyExitRange = 3});
    chassis.moveToPoint(-30, -23, 2000, {.maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(14);
    subsystems::matchload::extend();
    chassis.waitUntilDone();
    subsystems::matchload::retract();

    chassis.moveToPoint(-29, 23, 2000, {.maxSpeed = 80, .minSpeed = 40, .earlyExitRange = 1});
    chassis.waitUntil(35);
    subsystems::matchload::extend();

    chassis.cancelMotion();
    chassis.moveToPoint(-29, 21, 2000, {.maxSpeed = 50, .minSpeed = 40, .earlyExitRange = 1});


    chassis.moveToPoint(-46, 45 , 2000, {.maxSpeed = 70, .minSpeed = 40, .earlyExitRange = 1});


    chassis.turnToPoint(-70, 45, 1000, {.earlyExitRange = 1});
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);

    chassis.moveToPoint(-22, 48, 1000, {.forwards = false, .maxSpeed = 60});
    chassis.waitUntil(10);
    //score third high  goal
    //
    //

    chassis.waitUntilDone();
    
    chassis.tank(50, 50);
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);

    pros::delay(100);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    chassis.tank(-127, -127);
    subsystems::matchload::extend();

    pros::delay(2300);
    chassis.setPose(-28, 43, 270);
    pros::delay(100);
    chassis.tank(0, 0);
    pros::delay(100);
    
    pros::delay(100);
    chassis.moveToPoint(-71.75, 41, 1600, {.maxSpeed = 50, .minSpeed = 45});
    chassis.waitUntil(8);
    //matchload 3
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);

    chassis.waitUntilDone();
    chassis.tank(-18, -18);
    pros::delay(200);
    chassis.tank(20, 20);
    pros::delay(900);
    chassis.tank(-7, -7);
    pros::delay(100);
    chassis.tank(25, 25);
    pros::delay(1100);
    chassis.tank(0, 0);
    pros::delay(200);

    
    chassis.moveToPoint(-28, 55, 2500, {.forwards = false, .maxSpeed = 65});

    chassis.waitUntilDone();
    chassis.waitUntil(10);
    subsystems::matchload::retract();

    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);

    chassis.moveToPoint(32, 53.25, 2500, {.forwards = false, .maxSpeed = 90});

    chassis.moveToPoint(39, 43.5, 2500, {.forwards = false, .maxSpeed = 70});

    chassis.moveToPoint(21, 43, 1300, {.forwards = false, .maxSpeed = 70});

    chassis.waitUntil(15);

    //second High goal score
    
    chassis.waitUntilDone();
    
    chassis.tank(50, 50);
    subsystems::intake::run(subsystems::intake::GoalType::LOW_GOAL);
    pros::delay(200);
    chassis.tank(-127, -110);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);

    pros::delay(800);
    chassis.tank(-127, -127);
    subsystems::matchload::extend();

    pros::delay(1100);

    chassis.tank(0, 0);
    pros::delay(100);
    chassis.setPose(28, 44.5, chassis.getPose().theta);
    pros::delay(100);

    chassis.moveToPoint(71, 45, 1500, {.maxSpeed = 60, .minSpeed = 40});
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);

    //matchload 4
    chassis.waitUntilDone();
    chassis.tank(-10, -10);
    pros::delay(200);
    chassis.tank(25, 25);
    pros::delay(1000); 
    chassis.tank(-10, -10);
    pros::delay(150);
    chassis.tank(15, 15);
    pros::delay(600);
    chassis.tank(0, 0);

    chassis.moveToPoint(23, 43.5, 1800, {.forwards = false, .maxSpeed = 75});

    
    subsystems::matchload::retract();
    chassis.waitUntilDone();
    
    chassis.tank(50, 50);
    pros::delay(100);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);
    chassis.tank(-127, -127);
    pros::delay(1800);
    chassis.tank(0, 0);
    pros::delay(100);


    // try parking
    chassis.setPose(28, 44, 90);
    pros::delay(100);
    subsystems::intake::run(subsystems::intake::GoalType::LONG_GOAL);


    chassis.moveToPoint(57.25, 34, 2000, {.maxSpeed = 65});    
    chassis.waitUntil(15);
    subsystems::intake::run(subsystems::intake::GoalType::HOLD_BALLS);

    chassis.moveToPoint(65.5, 6.5, 4000, {.minSpeed = 127});
    pros::delay(375);
    subsystems::matchload::extend();
    pros::delay(1200);
    subsystems::matchload::retract();

    chassis.waitUntilDone();

    

}
void tunePid() {
    chassis.setPose(-15, -42, 270);
    pros::delay(100);
    

    chassis.moveToPoint(-25, -50, 1300, {.maxSpeed = 85, .minSpeed = 70, .earlyExitRange = 2});
    subsystems::wing::retract();
    chassis.moveToPose(-20, -49.5, 270, 3500, {.forwards = false, .maxSpeed = 95, .minSpeed = 60, .earlyExitRange = 4});
    chassis.waitUntil(6);
    chassis.cancelMotion();
    chassis.moveToPose(-8, -50.25, 270, 4000, {.forwards = false, .maxSpeed = 95, .minSpeed = 85});
    
    while (chassis.getPose().x < -7) {
        pros::delay(20);
    }
    subsystems::wing::extend();
    chassis.cancelMotion();
    chassis.tank(0,0);
    //subsystems::wing::retract();
    subsystems::matchload::retract();
    //chassis.swingToHeading(270, lemlib::DriveSide::LEFT, 1000);
    //chassis.tank(30,0);
    pros::delay(10000000);
}
