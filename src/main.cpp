/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Benjamin Ruby                                             */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  53A's main competition program for the 2022-2023 season   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include <cmath>
#include <string>

using namespace vex;

// A global instance of competition
competition Competition;

//Global variables
float J2;
float J3;
bool intakeMode = false;
bool intakeDirection = true;
bool brainInfo = false;
int selectedAuton = 0;
const float wheelRadius = 3.25 / 2;
const float driveWidth = 13;
const float driveLength = 12;
const float turnRadius = hypotf(driveWidth, driveLength) / 2;

//Math functions
float toDegrees(float radians) {
  return (radians * 180) / M_PI;
}

float toRadians(float degrees) {
  return (degrees * M_PI) / 180;
}

float arcLength(float arcMeasure, float radius) {
  return toRadians(arcMeasure) * radius;
}

float arcMeasure(float arcLength, float radius) {
  return toDegrees(arcLength / radius);
}

//Flywheel functions
int printFlywheelSpeed() {
  //Make sure line 3 is clear before using
  while (1) {
    Controller1.Screen.setCursor(2, 0);
    Controller1.Screen.print("Motor speed: %.2f", Flywheel.velocity(rpm));
    Controller1.Screen.setCursor(3, 0);
    Controller1.Screen.print("Sensor speed: %.2f", FlywheelSensor.velocity(rpm));
    task::sleep(100);
  }
  return 0;
}

void setFlywheelSpeed(float speed, velocityUnits units = velocityUnits::pct) {
  Flywheel.spin(forward, speed, units);
  //FlywheelLower.spin(forward, speed, units);
}

void startFlywheel() {
  setFlywheelSpeed(100);
}

void stopFlywheel() {
  Flywheel.stop(coast);
  //FlywheelLower.stop(coast);
}

void changeFlywheelSpeed(float speedDifference) {
  float speed = Flywheel.velocity(percent);
  setFlywheelSpeed(speed + speedDifference);
}

void incrementFlywheelSpeed() {
  changeFlywheelSpeed(5);
}

void decrementFlywheelSpeed() {
  changeFlywheelSpeed(-5);
}

void slightlyIncrementFlywheelSpeed() {
  changeFlywheelSpeed(2);
}

void slightlyDecrementFlywheelSpeed() {
  changeFlywheelSpeed(-2);
}

void closestFlywheel() {
  setFlywheelSpeed(350, rpm);
}

//Intake functions
void toggleIntake() {
  intakeMode = !intakeMode;
}

void changeIntakeDirection() {
  intakeDirection = !intakeDirection;
}

void updateIntake() {
  if (Controller1.ButtonLeft.pressing()) {
    Intake.spin(intakeDirection ? forward : reverse, 5, pct);
    //IntakeLower.spin(intakeDirection ? forward : reverse, 5, pct);
  } else {
    Intake.spin(intakeDirection ? forward : reverse, intakeMode ? 100 : 0, pct);
    //IntakeLower.spin(intakeDirection ? forward : reverse, intakeMode ? 100 : 0, pct);
  }
}

void rotateRoller(float angle) {
  Intake.spinFor(forward, angle, degrees, 100, velocityUnits::pct, false);
  //IntakeLower.spinFor(forward, angle, degrees, 100, velocityUnits::pct, false);
}

void spinRoller() {
  rotateRoller(360);
}

//Info functions
void printFlywheelTemperature() {
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Flywheel Temperature: %d", (int) Flywheel.temperature(fahrenheit));
  /* Brain.Screen.setCursor(2,1);
  Brain.Screen.print("Back Flywheel Temperature: %d", (int) FlywheelLower.temperature(fahrenheit)); */
}

void toggleBrainInfo() {
  Brain.Screen.clearScreen();
  brainInfo = !brainInfo;
}

void printMotorTemperature() {
  Brain.Screen.clearScreen();
  while (!Brain.Screen.pressing()) {
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Left front: %f", LeftFront.temperature());
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Left top: %f", LeftTop.temperature());
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Left back: %f", LeftBack.temperature());
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Right front: %f", RightFront.temperature());
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print("Right top: %f", RightTop.temperature());
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print("Right back: %f", RightBack.temperature());
  }
  Brain.Screen.clearScreen();
}

void printAutonDescription() {
  std::string autonDescription;
  switch (selectedAuton) {
    case 0:
    autonDescription = "None";
    break;

    case 1:
    autonDescription = "Testing";
    break;

    case 2:
    autonDescription = "Right side, preloads to high goal";
    break;

    case 3:
    autonDescription = "Skills";
    break;

    case 4:
    autonDescription = "Preloads to low goal";
    break;

    case 5:
    autonDescription = "Spin roller";
    break;

    default:
    autonDescription = "Index out of bounds";
    break;
  }
  Brain.Screen.setCursor(12, 1);
  Brain.Screen.clearLine();
  Brain.Screen.print("Auton: %s", autonDescription.c_str());
}

void changeAuton() { //Auton selector
  if (selectedAuton >= 5) {
    selectedAuton = 0;
  } else {
    selectedAuton++;
  }
  printAutonDescription();
}

//Miscellaneous functions
void shoot() {
  Indexer.set(true);
  wait(0.2,sec);
  Indexer.set(false);
}

void expand() {
  Expander.set(true);
}

void calibrate() {
  InertialSensor.startCalibration();
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(0, 0, "Inertial sensor calibrating...");
  while (InertialSensor.isCalibrating()) {
    wait(10, msec);
  }
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(0, 0, "Calibration complete!");
}

void drawPreautonMenu() {
  Brain.Screen.clearScreen("000040");
  Brain.Screen.setPenColor(white);
  Brain.Screen.drawLine(50, 0, 52, 218);
  Brain.Screen.drawLine(0, 119, 50, 121);
  Brain.Screen.drawLine(0, 216, 50, 218);
  Brain.Screen.setCursor(4, 2);
  Brain.Screen.print("Calibrate inertial sensor");
  Brain.Screen.setCursor(9, 2);
  Brain.Screen.print("Print drive motor temperatures");
  Brain.Screen.setCursor(5, 25);
  Brain.Screen.print("Switch auton");
}

void brainPressEvent() {
  if (Brain.Screen.xPosition() <= 51) {
    if (Brain.Screen.yPosition() <= 120) {
      calibrate();
    } else {
    printMotorTemperature();
    }
  } else {
    changeAuton();
  }
}

//Drive functions
float driveCurve(float joystickPosition) { //Exponential function with adjustable constants to change curve
  float a = 3.53231;
  float b = 1.03442;
  float c = -4.18356;
  return fabs(joystickPosition) >= 5 ? (fabs(joystickPosition) / joystickPosition) * ((a * pow(b, fabs(joystickPosition))) + c) : 0;
}

void updateDriveSpeed() {
  J2 = Controller1.Axis2.position(percent);
  J3 = Controller1.Axis3.position(percent);
  float leftSpeed = driveCurve(J3);
  float rightSpeed = driveCurve(J2);
  //Controller1.Screen.setCursor(1, 0);
  //Controller1.Screen.print("%f, %f", leftSpeed, rightSpeed);
  LeftFront.spin(forward, leftSpeed, pct);
  LeftTop.spin(forward, leftSpeed, pct);
  LeftBack.spin(forward, leftSpeed, pct);
  RightFront.spin(forward, rightSpeed, pct);
  RightTop.spin(forward, rightSpeed, pct);
  RightBack.spin(forward, rightSpeed, pct);
}

void stopDrive() {
  LeftFront.stop();
  LeftTop.stop();
  LeftBack.stop();
  RightFront.stop();
  RightTop.stop();
  RightBack.stop();
}

void setDriveStopping(brakeType stopType) {
  LeftFront.setStopping(stopType);
  LeftTop.setStopping(stopType);
  LeftBack.setStopping(stopType);
  RightFront.setStopping(stopType);
  RightTop.setStopping(stopType);
  RightBack.setStopping(stopType);
}

void  setDriveTimeout(float time) {
  LeftFront.setTimeout(time, seconds);
  LeftTop.setTimeout(time, seconds);
  LeftBack.setTimeout(time, seconds);
  RightFront.setTimeout(time, seconds);
  RightTop.setTimeout(time, seconds);
  RightBack.setTimeout(time, seconds);
}

//Auton support functions
void move(float length, float speed, bool blocking = true) {
  float spinDistance = arcMeasure(length, wheelRadius) * (3.0 / 5);
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print(spinDistance);
  LeftFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  LeftTop.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  LeftBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  RightFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  RightTop.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  RightBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, blocking);
}

void rotateOneSideEncoder(float angle, turnType direction, float initialSpeed) {
  float length = arcLength(angle, turnRadius * 2);
  float spinDistance = (3.0 / 5) * arcMeasure(length, wheelRadius); //Adjusted for gear ratio
  float distanceSpun;
  float speed = initialSpeed;
  motor trackedMotor = direction == right ? LeftBack : RightBack; //Motor selection
  if (direction == right) {
    LeftFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
    LeftTop.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
    LeftBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  } 
  if (direction == left) {
    RightFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
    RightTop.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
    RightBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  }
  float initialPosition = trackedMotor.position(degrees);
  while (!trackedMotor.isDone()) { //Slow down when approaching target
    distanceSpun = fabs(initialPosition - trackedMotor.position(degrees));
    speed = initialSpeed * ((spinDistance - distanceSpun) / spinDistance);
    if (direction == right) {
      LeftFront.setVelocity(speed, pct);
      LeftTop.setVelocity(speed, pct);
      LeftBack.setVelocity(speed, pct);
    }
    if (direction == left) {
      RightFront.setVelocity(speed, pct);
      RightTop.setVelocity(speed, pct);
      RightBack.setVelocity(speed, pct);
    }
  }
  stopDrive();
}

void rotateBothSidesEncoder(float angle, turnType direction, float initialSpeed) {
  float length = arcLength(angle, turnRadius);
  float spinDistance = (3.0 / 5) * arcMeasure(length, wheelRadius);
  float speed = initialSpeed;
  float initialPosition = RightBack.position(degrees);
  float distanceSpun;
  LeftFront.spinFor(direction == left ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  LeftTop.spinFor(direction == left ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  LeftBack.spinFor(direction == left ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  RightFront.spinFor(direction == right ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  RightTop.spinFor(direction == right ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  RightBack.spinFor(direction == right ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  while (!RightBack.isDone()) {
    distanceSpun = fabs(initialPosition - RightBack.position(degrees));
    speed = initialSpeed * ((spinDistance - distanceSpun) / spinDistance);
    Controller1.Screen.setCursor(3, 0);
    Controller1.Screen.print(speed);
    LeftFront.setVelocity(speed, pct);
    LeftTop.setVelocity(speed, pct);
    LeftBack.setVelocity(speed, pct);
    RightFront.setVelocity(speed, pct);
    RightTop.setVelocity(speed, pct);
    RightBack.setVelocity(speed, pct);
  }
  stopDrive();
}

void rotateOneSideInertial(float angle, turnType direction, float initialSpeed) {
  float speed = initialSpeed;
  float currentAngle = 0;
  InertialSensor.resetRotation();
  while (fabs(angle - currentAngle) < 1) {
    currentAngle = InertialSensor.angle();
    speed = initialSpeed * ((angle - currentAngle) / angle);
    Controller1.Screen.setCursor(3, 0);
    Controller1.Screen.print(speed);
    if (direction == right) {
      LeftFront.spin(forward, speed, pct);
      LeftTop.spin(forward, speed, pct);
      LeftBack.spin(forward, speed, pct);
    }
    if (direction == left) {
      RightFront.spin(forward, speed, pct);
      RightTop.spin(forward, speed, pct);
      RightBack.spin(forward, speed, pct);
    }
  }
  stopDrive();
}

void rotateBothSidesInertial(float angle, turnType direction, float initialSpeed) {
  float speed = initialSpeed;
  float currentAngle = 0;
  InertialSensor.resetRotation();
  while (fabs(angle - currentAngle) < 1) {
    currentAngle = InertialSensor.angle();
    speed = initialSpeed * ((angle - currentAngle) / angle);
    Controller1.Screen.setCursor(3, 0);
    Controller1.Screen.print(speed);
    LeftFront.spin(direction == right ? forward : reverse, speed, pct);
    LeftTop.spin(direction == right ? forward : reverse, speed, pct);
    LeftBack.spin(direction == right ? forward : reverse, speed, pct);
    RightFront.spin(direction == left ? forward : reverse, speed, pct);
    RightTop.spin(direction == left ? forward : reverse, speed, pct);
    RightBack.spin(direction == left ? forward : reverse, speed, pct);
  }
  stopDrive();
}

void rotateOneSide(float angle, turnType direction, float initialSpeed = 100, float inertial = true) {
  if (inertial) {
    rotateOneSideInertial(angle, direction, initialSpeed);
  } else {
    rotateOneSideEncoder(angle, direction, initialSpeed);
  }
}

void rotateBothSides(float angle, turnType direction, float initialSpeed = 100, float inertial = true) {
  if (inertial) {
    rotateBothSidesInertial(angle, direction, initialSpeed);
  } else {
    rotateBothSidesEncoder(angle, direction, initialSpeed);
  }
}

//Auton functions
void test() { //1
  rotateBothSides(90, left, 50);
  wait(1, seconds);
  rotateBothSides(90, right, 50);
  wait(1, seconds);
  rotateOneSide(90, left, 50);
  wait(1, seconds);
  rotateOneSide(90, right, 50);
  wait(1, seconds);
}
void rightSimple() { //2
  setFlywheelSpeed(73);
  wait(0.5, seconds);
  rotateOneSide(-22, left, 30);
  wait(5, seconds);
  shoot();
  setFlywheelSpeed(70);
  wait(2, seconds);
  shoot();
}

void skills() { //3
  startFlywheel();
  setDriveTimeout(5);
  move(3, 20);
  rotateRoller(150);
  wait(3, seconds);
  shoot();
  wait(1, seconds);
  shoot();
  wait(0.5, seconds);
  move(-20, 100);
  wait(0.5, seconds);
  rotateBothSides(90, left);
  wait(0.5, seconds);
  move(10, 100);
}

void lowGoal() { //4
  startFlywheel();
  wait(5, seconds);
  shoot();
  wait(3, seconds);
  shoot();
}

void roller() { //5
  setDriveTimeout(5);
  move(1.5, 20);
  rotateRoller(360);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Indexer.set(false);
  Expander.set(false);
  Brain.Screen.pressed(brainPressEvent);
}

void autonomous(void) {
  Indexer.set(false);
  Expander.set(false);
  Intake.setStopping(coast);
  //IntakeLower.setStopping(coast);
  setDriveStopping(hold);
  calibrate();
  switch (selectedAuton) {
    case 1:
    test();
    break;

    case 2:
    rightSimple();
    break;

    case 3:
    skills();
    break;

    case 4:
    lowGoal();
    break;

    case 5:
    roller();
    break;
  }
}

void usercontrol(void) {
  Controller1.Screen.clearScreen();
  Flywheel.setStopping(coast);
  //FlywheelLower.setStopping(coast);
  Intake.setStopping(coast);
  //IntakeLower.setStopping(coast);
  Indexer.set(false);
  Expander.set(false);
  Controller1.ButtonR1.pressed(incrementFlywheelSpeed);
  Controller1.ButtonR2.pressed(decrementFlywheelSpeed);
  Controller1.ButtonL1.pressed(toggleIntake);
  Controller1.ButtonL2.pressed(changeIntakeDirection);
  Controller1.ButtonB.pressed(shoot);
  Controller1.ButtonX.pressed(stopFlywheel);
  Controller1.ButtonA.pressed(startFlywheel);
  Controller1.ButtonY.pressed(spinRoller);
  Controller1.ButtonRight.pressed(closestFlywheel);
  Controller1.ButtonUp.pressed(slightlyIncrementFlywheelSpeed);
  Controller1.ButtonDown.pressed(slightlyDecrementFlywheelSpeed);
  task flyWheelSpeed(printFlywheelSpeed);
  setDriveStopping(brake);
  while (true) {
    updateDriveSpeed();
    updateIntake();
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
