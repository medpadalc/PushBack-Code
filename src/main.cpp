#include "main.h"


pros::MotorGroup leftMotors({2, 1, 3}, pros::MotorCartridge::blue);
pros::MotorGroup rightMotors({-5, -4, -6}, pros::MotorCartridge::blue);
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 11.5,
    lemlib::Omniwheel::NEW_325, 450, 8);

pros::MotorGroup mainIntake({9, -10});
pros::Motor endIntake(20);

pros::Imu imu(15);

pros::Rotation verticalTrackingWheelRotation(5);
lemlib::TrackingWheel verticalTrackingWheel(&verticalTrackingWheelRotation, 2, 0);

pros::Rotation horizontalTrackingWheelRotation(8);
lemlib::TrackingWheel horizontalTrackingWheel(&horizontalTrackingWheelRotation, 2, -5);


lemlib::OdomSensors sensors(&verticalTrackingWheel,
                            &horizontalTrackingWheel,
                            nullptr,
                            nullptr,
                            &imu // inertial sensor
);


// lateral PID controller
lemlib::ControllerSettings linearSettings(10, // proportional gain (kP)
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
lemlib::ControllerSettings angularSettings(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in degrees
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

/*Distance frontDistanceSensor(11, {0, 0, 0});
Distance rightDistanceSensor(12, {0, 0, -M_PI_2});
Distance leftDistanceSensor(13, {0, 0, M_PI_2});
std::vector pfSensors = {&frontDistanceSensor, &rightDistanceSensor, &leftDistanceSensor};
*/

lemlib::Chassis chassis(drivetrain, linearSettings, angularSettings,
    sensors);


rd::Selector selector({
    {"Solo AWP", solo_awp},
    {"Left", left},
    {"Right", right},
    {"Tune", tunePid}
});

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::adi::Pneumatics matchload('G', true);
pros::adi::Pneumatics hood('A', false);

/**
 * @brief Initializes the robot's motors and sensors.
 *
 * This function sets motor brake modes and encoder units during initialization.
 */
void initialize() {
    printf("Starting logging");
    chassis.calibrate();
    chassis.setPose(0, 0, 0);
    
    pros::Task{[&]() {
        while (true) {
            lemlib::Pose pose = chassis.getPose(false, false);
            controller.print(0, 0, "%.1f", imu.get_heading());
            //controller.print(0, 0, "X: %.1f Y: %.1f θ: %.1f", pose.x, pose.y, pose.theta);
            pros::delay(1000);
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
    while (true) {
        int32_t leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int32_t rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        auto [throttle, turn] = driveCurve({leftY, rightX});
        chassis.tank(throttle - turn, throttle + turn, true);
        
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            mainIntake.move(127);
            endIntake.move(-127);
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            mainIntake.move(127);
            endIntake.move(127);
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            mainIntake.move(-127);
            endIntake.move(-127);
        }
        else {
            mainIntake.move(0);
            endIntake.move(0);
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
            hood.toggle();
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            matchload.toggle();
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            autonomous();
        }
        lemlib::Pose pose = chassis.getPose(false, false);
        
        //controller.print(0, 0, "X: %.1f Y: %.1f θ: %.1f", pose.x, pose.y, pose.theta);
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
    tunePid();
    //selector.run_auton();
}
