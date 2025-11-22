#include "main.h"


pros::MotorGroup leftMotors({-4, -5, -6}, pros::MotorCartridge::blue);
pros::MotorGroup rightMotors({2, 1, 3}, pros::MotorCartridge::blue);
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 11.5,
    lemlib::Omniwheel::NEW_325, 450, 8);

pros::Imu imu(7);

pros::Rotation horizontalTrackingWheelRotation(-8);
lemlib::TrackingWheel verticalTrackingWheel(&horizontalTrackingWheelRotation, lemlib::Omniwheel::NEW_275, 0.5);


lemlib::OdomSensors sensors(&verticalTrackingWheel,
                            nullptr,
                            nullptr,
                            nullptr,
                            &imu // inertial sensor
);


// lateral PID controller
lemlib::ControllerSettings linearSettings(7, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angularSettings(1.65, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);
/*
Distance frontDistanceSensor(11, {0, 0, 0});
Distance rightDistanceSensor(12, {0, 0, -M_PI_2});
Distance leftDistanceSensor(13, {0, 0, M_PI_2});
*/
std::vector<Distance*> pfSensors = {};


localization::UpgradedChassis<PARTICLES> chassis(drivetrain, linearSettings, angularSettings,
    sensors, pfSensors);


rd::Selector selector({
    {"Solo AWP", solo_awp},
    {"Left", left},
    {"Right", right},
    {"Tune", tunePid}, 
    {"Skills", skills}
});

pros::Controller controller(pros::E_CONTROLLER_MASTER);


/**
 * @brief Initializes the robot's motors and sensors.
 *
 * This function sets motor brake modes and encoder units during initialization.
 */
void initialize() {
    printf("Starting logging");
    chassis.calibrate();
    subsystems::intake::setAllianceColor(subsystems::intake::AllianceColor::DISABLED);
    
    
    pros::Task{[&]() {
        while (true) {     
            lemlib::Pose pose = chassis.getPose(false, false);
            controller.print(0, 0, "%s X: %.1f Y: %.1f θ: %.1f",
            subsystems::intake::getAllianceColorAsString().c_str(), pose.x, pose.y, pose.theta);
            pros::delay(50);
        }
    }};
    
}


/**
 * @brief Runs the operator control loop.
 *
 * This function continuously reads controller inputs, processes them,
 * and applies movement commands to the robot's motors.
 */
void opcontrol() {
    subsystems::intake::stop();
    while (true) {
        // drivetrain
        int32_t leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int32_t rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        auto [throttle, turn] = driveCurve({leftY, rightX});
        chassis.tank(throttle + turn, throttle - turn, true);
        
        // intake
        subsystems::intake::GoalType goal = subsystems::intake::GoalType::NONE;
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            goal = subsystems::intake::GoalType::MEDIUM_GOAL;
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            goal = subsystems::intake::GoalType::LONG_GOAL;
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            goal = subsystems::intake::GoalType::LOW_GOAL;
        }
        subsystems::intake::iterate(goal);

        // intake colorsort
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            subsystems::intake::toggleAllianceColor();
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            subsystems::intake::disableColorSort();
        }

        // pneumatics
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            subsystems::hood::toggle();
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
            subsystems::matchload::toggle();
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            subsystems::wing::toggle();
        }
        
        // autos
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            autonomous();
            //solo_awp();
        }

        pros::delay(10);
    }
}

/**
 * @brief Runs when the robot is disabled in competition mode.
 */
void disabled() {}

/**
 * @brief Runs before autonomous mode in competition settings.
 *
 * This function is useful for setting up autonomous routines, such as
 * selecting different strategies using an LCD screen.
 */
void competition_initialize() {}

/**
 * @brief Runs the autonomous routine.
 *
 * This function is executed when the robot enters autonomous mode in competition.
 */
void autonomous() {
    selector.run_auton();
}
