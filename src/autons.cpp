#include "autons.hpp"


void solo_awp() {
    chassis.setPose(-62.5, -17, 90);
    pros::delay(100);
    chassis.moveToPoint(-55, -15, 2000, {.maxSpeed = 100, .minSpeed = 40, .earlyExitRange = 2});
    pros::Motor front(-10);
    pros::Motor middle(9);
    chassis.moveToPoint(-37, -35, 2000, {.maxSpeed = 85, .minSpeed = 25, .earlyExitRange = 3});
    pros::delay(300);
    matchload.extend();
    chassis.moveToPoint(-60, -47, 2000, {.maxSpeed = 70,.earlyExitRange = 2});
    front.move(100);
    chassis.moveToPoint(-22, -47, 2200, {.forwards = false, .maxSpeed = 70});
    pros::delay(1000);
    middle.move(127);
    endIntake.move(127);
    matchload.retract();
    chassis.waitUntilDone();
    pros::delay(400);
    chassis.moveToPoint(-35, -47, 3000, {.maxSpeed = 85, .minSpeed = 20, .earlyExitRange = 1});
    chassis.moveToPoint(-23, -22, 3000, {.maxSpeed = 85, .minSpeed = 20, .earlyExitRange = 1});
    pros::delay(200);
    middle.move(0);
    endIntake.move(0);
    chassis.moveToPose(-11, -8.5,45, 2000, {.maxSpeed = 50, .earlyExitRange = 0.5});
    pros::delay(1000);
    front.move(-127);
    middle.move(-127);
    chassis.waitUntilDone();
    pros::delay(300);
    chassis.moveToPoint(-23, -22, 750, {.forwards = false, .maxSpeed = 90, .minSpeed = 30});

    chassis.moveToPoint(-24, 24, 3000, {.maxSpeed = 70, .minSpeed = 30, .earlyExitRange = 1});
    front.move(100);
    chassis.moveToPose(-13.5, 10.5,315, 2000, {.forwards = false, .maxSpeed = 50});
    pros::delay(1000);
    front.move(100);
    middle.move(127);
    endIntake.move(-127);
    chassis.waitUntilDone();
    pros::delay(2000);
    chassis.moveToPoint(-40, 46, 2500, {.maxSpeed = 70, .earlyExitRange = 3});
    front.move(100);
    chassis.turnToHeading(-90, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();
    chassis.moveToPoint(-30, 48, 3000, {.forwards = false, .maxSpeed = 70});
    pros::delay(500);
    endIntake.move(127);
    mainIntake.move(127);
    matchload.extend();
    chassis.waitUntilDone();


    hood.retract();

    pros::delay(1000);
    chassis.moveToPoint(-90, 48, 3500, {.maxSpeed = 90});
    hood.extend();
    chassis.waitUntilDone();
    pros::delay(500);

    chassis.moveToPoint(-30, 48, 2000, {.forwards = false, .maxSpeed = 70});
    mainIntake.move(0);
    hood.retract();
    chassis.waitUntilDone();
    mainIntake.move(127);
    pros::delay(500);
}

void left() {
    hood.extend();
    chassis.setPose(-63, 15.5, 90);
    pros::delay(100);
    chassis.moveToPoint(-43, 15, 2000, {.maxSpeed = 70});
    chassis.moveToPoint(-20, 22, 2000, {.maxSpeed = 30});

    pros::Motor front(-10);
    pros::Motor middle(9);
    middle.move(-20);
    front.move(127);
    chassis.waitUntilDone();
    pros::delay(500);
    chassis.moveToPose(-9, 9,315, 2000, {.forwards = false, .maxSpeed = 50});
    pros::delay(1700);
    front.move(127);
    middle.move(100);
    endIntake.move(-100);
    chassis.waitUntilDone();
    pros::delay(1200);
    chassis.moveToPoint(-40, 46, 2500, {.maxSpeed = 70, .earlyExitRange = 3});
    front.move(100);
    chassis.turnToHeading(-90, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();


    matchload.extend();
    chassis.waitUntilDone();
    mainIntake.move(127);
    hood.retract();
    endIntake.move(127);
    pros::delay(700);
    chassis.moveToPoint(-90, 48, 2000, {.maxSpeed = 70});
    hood.extend();
    chassis.waitUntilDone();
    pros::delay(300);

    chassis.moveToPoint(-25, 48, 2000, {.forwards = false, .maxSpeed = 70});


    hood.retract();
    chassis.waitUntilDone();
    mainIntake.move(127);
    endIntake.move(127);

    pros::delay(1500);
}

void right() {
    hood.extend();
    chassis.setPose(-63, -18, 90);
    pros::delay(100);
    chassis.moveToPoint(-43, -15, 2000, {.maxSpeed = 70});
    chassis.moveToPoint(-20, -22, 2000, {.maxSpeed = 40});

    pros::Motor front(-10);
    pros::Motor middle(9);
    middle.move(-5);
    front.move(127);
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.moveToPose(-13.5, -11.5,45, 2000, {.maxSpeed = 50});
    pros::delay(750);
    chassis.cancelMotion();
    chassis.moveToPose(-12, -10.5,45, 2000, {.maxSpeed = 35});
    pros::delay(400);
    front.move(-127);
    middle.move(-127);
    chassis.waitUntilDone();
    pros::delay(800);
    chassis.moveToPoint(-40, -45.5, 2000, {.forwards = false, .maxSpeed = 70, .earlyExitRange = 3});
    pros::delay(500);
    front.move(100);
    middle.move(0);
    chassis.turnToHeading(-90, 2000, {.maxSpeed = 70});
    chassis.waitUntilDone();
    chassis.moveToPoint(-22, -46.5, 1300, {.forwards = false, .maxSpeed = 70});
    hood.extend();
    mainIntake.move(127);
    pros::delay(800);
    matchload.extend();

    mainIntake.move(127);
    hood.retract();
    endIntake.move(127);
    pros::delay(800);
    chassis.moveToPoint(-92, -45.5, 2200, {.maxSpeed = 60});
    hood.extend();
    chassis.waitUntilDone();
    pros::delay(500);

    chassis.moveToPoint(-25, -46.5, 2000, {.forwards = false, .maxSpeed = 70});
    mainIntake.move(127);

    chassis.waitUntilDone();
    hood.retract();
    mainIntake.move(127);
    endIntake.move(127);
    pros::delay(2500);
}
void tunePid(){
    chassis.setPose(-48, -14, 180);
    pros::delay(200);
    chassis.moveToPoint(-48, -47, 5000, {.maxSpeed = 40});
    matchload.extend();
    chassis.moveToPoint(-75, -47, 4000, {.maxSpeed = 50});
    mainIntake.move(127);
    hood.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-75, -47, 3000, {.maxSpeed = 50});
    hood.retract();
    endIntake.move(127);
    pros::delay(4000);

}
