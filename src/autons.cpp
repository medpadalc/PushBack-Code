#include "autons.hpp"


void solo_awp() {
   // chassis.setPose()
}

void left() {

}

void right() {

}
void tunePid(){
    chassis.setPose(0, 0, 0);
    chassis.turnToHeading(360, 5000);
}
