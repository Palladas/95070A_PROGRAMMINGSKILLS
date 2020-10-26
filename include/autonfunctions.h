#include "main.h"
#include "motorsetup.h"
#include <string>


//This file contains all functions that we use in our autonomous

//Moves the left hand side of the drivetrain
void moveLeft(int voltage){
  LeftDrive.move(voltage);
  LeftBack.move(voltage);
}

//Moves Right hand side of the drivetrain
void moveRight(int voltage) {
  RightDrive.move(voltage);
  RightBack.move(voltage);
}

//gets if an integer is positive or negative
double getSign(double input){
  if(input > 0){
    return 1;
  }else if(input < 0){
    return -1;
  }else{
    return 0;
  }
}

//moves the entire drivetrain at a certain speed. The speed is defined when we call the function.
void moveDriveTrain(double speed){
  LeftDrive.move(speed);
  RightDrive.move(speed);
  LeftBack.move(speed);
  RightBack.move(speed);
}

//moves each side of the drivetrain at a different voltage; used for turning in autonomous, and in our driver control program
void moveDriveTrainv(double leftvoltage, double rightvoltage){
  LeftDrive.move_voltage(leftvoltage);
  RightDrive.move_voltage(rightvoltage);
  LeftBack.move_voltage(leftvoltage);
  RightBack.move_voltage(rightvoltage);
}
//moves each side at a different speed
void moveDriveTrain(double leftSpeed, double rightSpeed){
  LeftDrive.move(leftSpeed);
  LeftBack.move(leftSpeed);
  RightDrive.move(rightSpeed);
  RightBack.move(rightSpeed);
}

//Returns the position of the gyro
int GyroPos() {
return (int(gyro.get_value()) / 10);
}



//Turns the robot to the target position
void Rotate(int TargetPos, int speed) {
  bool IsLeft;//turning left true/false
  gyro.reset();//reset Gyro
//Turning clockwise
  if (TargetPos > 0) {
    LeftDrive.move(speed);
    RightDrive.move(-speed);
    LeftBack.move(speed);
    RightBack.move(-speed);
    IsLeft = true;
}
//turning counterclockwise
  else {
    LeftDrive.move(-speed);
    RightDrive.move(speed);
    LeftBack.move(-speed);
    RightBack.move(speed);
    IsLeft = false;
}
//reads where the gyro is at a given time, and where we want to rotate to
  TargetPos = TargetPos / 2;
  TargetPos = TargetPos + (GyroPos() / 2);
//If a desired turn is greater than 180 degrees, it calculates how much to turn in the other direction, saving time
  if (TargetPos > 180) {
    TargetPos = TargetPos - 180;
  }
//opposite of above statement
  if (TargetPos < -180) {
    TargetPos = TargetPos + 180;
}

//turns the correct amount in the clockwise direction
  if (IsLeft == true) {
    while (TargetPos >= (GyroPos() / 2)) {
    pros::delay(20);
    }
    LeftDrive.move(0);
    RightDrive.move(0);
}
//turns the correct amount in the counterclockwise direction
  else {
    while (TargetPos <= (GyroPos() / 2)) {
    pros::delay(20);
    }
    LeftDrive.move(0);
    RightDrive.move(0);
  }

}

//moves the drivetrain in encoder ticks
void encoderMove(double distance, double power){
  double encoderticks = distance*900 / (4*M_PI); //converts distance into encoder ticks
  LeftDrive.move_relative(encoderticks, power);
  RightDrive.move_relative(encoderticks, power);
  LeftBack.move_relative(encoderticks, power);
  RightBack.move_relative(encoderticks, power);
  pros::delay(1500);
}

//moves the intakes and the flywheel forward
void moveIntakesD(double voltage){
  if (getSign(voltage) == 1){
    LeftIntake.move(voltage);
    RightIntake.move(voltage);
    FlyWheel.move(voltage);
    Rollers.move(voltage);
  }
  //moves the intakes backwards, but does not run the flywheel
  else if(getSign(voltage) == -1){
    LeftIntake.move(voltage);
    RightIntake.move(voltage);
    Rollers.move(voltage);
  }else{
    LeftIntake.move(0);
    RightIntake.move(0);
    FlyWheel.move(0);
    Rollers.move(0);
  }
}
//moves the intakes at a certain voltage
void moveIntakes(double voltage){
  LeftIntake.move(voltage);
  RightIntake.move(voltage);
  Rollers.move(voltage);
}
//moves the intakes for a certian time at an indicated voltage
void moveIntakes(double voltage, double time){
  moveIntakes(voltage);
  pros::delay(time);
  moveIntakes(0);
}

//moves the drivetrain and intakes at the same time
void driveintake(double distance){
  double encoderticks = distance*900 / (4*M_PI);
  LeftDrive.move_relative(encoderticks, 100);
  RightDrive.move_relative(encoderticks, 100);
  LeftBack.move_relative(encoderticks, 100);
  RightBack.move_relative(encoderticks, 100);
  LeftIntake.move(127);
  RightIntake.move(127);
  Rollers.move(120);
  pros::delay(1000);
}
//runs the intakes and the flywheel at the same time, for a different amount of time depending on the number of balls
void score(double balls){
  FlyWheel.move(127);
  pros::delay(2000);
  Rollers.move(127);
  pros::delay(1000 * balls);
  FlyWheel.move(0);
  Rollers.move(0);
}
//prints a statement on the controller to help us debug our code
void print(double step){
  control.print(0, 0, "STEP: %d", std::to_string(step));
}
