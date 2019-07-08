#include "main.h"

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
 #define LEFT_WHEELS_PORT 1
 #define RIGHT_WHEELS_PORT 10

 int deadBand = 10;					// dead zone detection

 void opcontrol() {
 	pros::Controller master(pros::E_CONTROLLER_MASTER);
 	pros::Motor left_mtr(LEFT_WHEELS_PORT);
 	pros::Motor right_mtr(RIGHT_WHEELS_PORT, true);	// reverse motor
 	while (true) {
		int left_speed = master.get_analog(ANALOG_LEFT_Y);
		int right_speed = master.get_analog(ANALOG_RIGHT_Y);

		if(std::abs(left_speed) <= deadBand) { left_speed = 0; }
		if(std::abs(right_speed) <= deadBand) { right_speed = 0; }

 		left_mtr.move(left_speed);
 		right_mtr.move(right_speed);

 		pros::delay(20);
 	}
 }
