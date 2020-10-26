#include "main.h"
#include "autonfunctions.h"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
 //Pre-Generated Pros Code

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

//Initializes Odometry
std::shared_ptr<okapi::OdomChassisController> chassis =
  okapi::ChassisControllerBuilder()
    .withMotors({4, 12}, {3, 2})
    .withDimensions(okapi::AbstractMotor::gearset::green, {{4_in, 13.25_in}, okapi::imev5GreenTPR})
    .withOdometry()
		.buildOdometry();



//Runs this code when the program runs
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
	LeftDrive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	RightDrive.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  LeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
  RightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	RightIntake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	LeftIntake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	Rollers.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  FlyWheel.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  pros::delay(1);

}

//Other stuff generated automatically by PROS
void disabled() {}
void competition_initialize() {}

//Is the function that runs when autonomous is started
void autonomous() {
  driveintake(30);
	pros::delay(500);
  moveIntakes(0);
	Rollers.move_relative(-450, 100);
	pros::delay(300);
  encoderMove(10, 80);
	pros::delay(500);
  chassis->turnToAngle(-90_deg);
	chassis->moveDistance(36_in);
	pros::delay(500);
	chassis->turnToAngle(177_deg);
	chassis->moveDistance(31_in);
	pros::delay(500);
	score(2);
}

//Initializes buttons on the contoller
 #define Xkey control.get_digital(E_CONTROLLER_DIGITAL_X)
 #define Ykey control.get_digital(E_CONTROLLER_DIGITAL_Y)
 #define Akey control.get_digital(E_CONTROLLER_DIGITAL_A)
 #define Bkey control.get_digital(E_CONTROLLER_DIGITAL_B)
 #define UPkey control.get_digital(E_CONTROLLER_DIGITAL_UP)
 #define DOWNkey control.get_digital(E_CONTROLLER_DIGITAL_DOWN)
 #define LEFTkey control.get_digital(E_CONTROLLER_DIGITAL_LEFT)
 #define RIGHTkey control.get_digital(E_CONTROLLER_DIGITAL_RIGHT)
 #define LEFTUPkey control.get_digital(E_CONTROLLER_DIGITAL_L1)
 #define LEFTDOWNkey control.get_digital(E_CONTROLLER_DIGITAL_L2)
 #define RIGHTUPkey control.get_digital(E_CONTROLLER_DIGITAL_R1)
 #define RIGHTDOWNkey control.get_digital(E_CONTROLLER_DIGITAL_R2)
 #define LEFTX control.get_analog(E_CONTROLLER_ANALOG_LEFT_X)
 #define LEFTY control.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)
 #define RIGHTX control.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)
 #define RIGHTY control.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)
//DRIVER CONTROL FUNCTIONS

//Controls the drivetrain movement
void DRIVETRAINMOVEMENT(){
  moveDriveTrain(RIGHTY*4/3, LEFTY*4/3);
}

//Controls the movement of the intakes
void intake(){
	if(RIGHTUPkey){
		moveIntakesD(127);
	}else if(LEFTDOWNkey){
		moveIntakesD(-127);

	}else if(LEFTUPkey){
    FlyWheel.move(200);
  }else if(RIGHTDOWNkey){
    Rollers.move(200);
  }else if(Xkey){
    FlyWheel.move(-80);
  }

  else{
		moveIntakesD(0);
	}
}

//MAIN DRIVERCONTROL FUNCTION
void opcontrol() {
  //Sets the default odometry position.
  chassis->setState({36_in, 0_in, 0_deg});
	while (true) {
		DRIVETRAINMOVEMENT();
		intake();
    //Calls autonomus when the A-Key is pressed
		if(Akey){
			autonomous();
		}
		if (Bkey){
			chassis->turnToAngle(270_deg);
		}
		pros::delay(100);
	}
}
