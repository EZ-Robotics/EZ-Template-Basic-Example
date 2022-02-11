#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


// Chassis constructor 
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  {1, 2}

  // Right Chassis Ports (negative port will reverse it!)
  ,{-3, -4}

  // IMU Port
  ,5

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  ,4.125

  // Cartridge RPM
  ,200

  // External Gear Ratio (MUST BE DECIMAL)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1
);



/**
 * Default PID constants, this is run in initialize. 
 *
 * To tune, read this tutorial
 * https://ez-robotics.github.io/EZ-Template/docs/Tutorials/tuning_constants.html
 */
void default_constants() {
  chassis.set_pid_constants(&chassis.headingPID, 5, 0, 0, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.3, 0, 0, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.3, 0, 0, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0, 0, 0);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 0, 0);
}



/**
 * Example Autonomous Routines 
 *
 * To tune, read this tutorial
 * https://ez-robotics.github.io/EZ-Template/docs/Tutorials/tuning_constants.html
 */
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at out of 127.

  chassis.set_drive_pid(24, 110);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, 110);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, 110);
  chassis.wait_drive();
}

// Turn Example
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at out of 127

  chassis.set_turn_pid(90, 110);
  chassis.wait_drive();

  chassis.set_turn_pid(45, 110);
  chassis.wait_drive();

  chassis.set_turn_pid(0, 110);
  chassis.wait_drive();
}

// Combining Turn + Drive
void drive_and_turn() {
  chassis.set_drive_pid(24, 110);
  chassis.wait_drive();

  chassis.set_turn_pid(45, 110);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, 110);
  chassis.wait_drive();

  chassis.set_turn_pid(0, 110);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, 110);
  chassis.wait_drive();
}



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  default_constants(); // Set the drive to your own constants from autons.cpp!

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.add_autons({
    Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {

    chassis.tank(); // Tank control

    // . . .
    // Put more user control code here!
    // . . .

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
