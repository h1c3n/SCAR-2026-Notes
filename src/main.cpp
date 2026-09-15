#include "main.h"


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * Code in initialize will be run at the beginning of both driver and auton
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

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
void autonomous() {}

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
 * 
 * Some code in driver control will take place in a loop with pros::delay(), if you don’t have any delays the code will not work
 * All driver controls are to be written within the while true loop
 * The loop functions as a task that is constantly running in the background
 */
void opcontrol() {

	/*
	* the following code initializes the controller object and motor groups for left and right sides of the drivetrain 
	* motors geared in reverse will need to be reversed (adding a negative sign in front of the port number)
	* reversed ports can be identified from the brain,
	* select a port number and apply clockwise rotation, if the motor moves in opposite direction, you must reverse this port
	* ports must be accurate for the rest of the code to function
	*/
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({1, -2, 3});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-4, 5, -6});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6


	while (true) {

		// Arcade control scheme
		// sample code for week 1 activity 1
		/*
		* analog values refer to joysticks, ranging from -127 to 127
		* .move() sets the voltage for the motors in the motor group from -127 to 127
		* the following code simply takes an analog value from the master Controller object and set the voltage to our motor groups
		*/
		int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
		/*
		* motor command = foward value + turning value
		* turning must apply opposite effect for the 2 sides 
		* ex: as left side slows down, the right side speeds up, so the robot curves toward the slower side.
		*/
		left_mg.move(dir - turn);                      // Sets left motor voltage
		right_mg.move(dir + turn);                     // Sets right motor voltage
		pros::delay(10);                               // Run for 10 ms then update
	}
}