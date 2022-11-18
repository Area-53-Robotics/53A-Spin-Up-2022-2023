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

using namespace vex;

// A global instance of competition
competition Competition;

//Global variables
float J2;
float J3;
bool intakeMode = false;
bool intakeDirection = true;
bool brainInfo = false;
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
    Controller1.Screen.print("Motor speed: %.2f", FlywheelHigher.velocity(rpm));
    Controller1.Screen.setCursor(3, 0);
    Controller1.Screen.print("Sensor speed: %.2f", FlywheelSensor.velocity(rpm));
    task::sleep(100);
  }
  return 0;
}

void setFlywheelSpeed(float speed, velocityUnits units = velocityUnits::pct) {
  FlywheelHigher.spin(forward, speed, units);
  FlywheelLower.spin(forward, speed, units);
}

void startFlywheel() {
  setFlywheelSpeed(100);
}

void stopFlywheel() {
  FlywheelHigher.stop(coast);
  FlywheelLower.stop(coast);
}

void changeFlywheelSpeed(float speedDifference) {
  float speed = FlywheelHigher.velocity(percent);
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
    IntakeHigher.spin(intakeDirection ? forward : reverse, 5, pct);
    IntakeLower.spin(intakeDirection ? forward : reverse, 5, pct);
  } else {
    IntakeHigher.spin(intakeDirection ? forward : reverse, intakeMode ? 100 : 0, pct);
    IntakeLower.spin(intakeDirection ? forward : reverse, intakeMode ? 100 : 0, pct);
  }
}

void rotateRoller(float angle) {
  IntakeHigher.spinFor(forward, angle, degrees, 100, velocityUnits::pct, false);
  IntakeLower.spinFor(forward, angle, degrees, 100, velocityUnits::pct, false);
}

void spinRoller() {
  rotateRoller(360);
}

//Info functions
void printFlywheelTemperature() {
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Front Flywheel Temperature: %d", (int) FlywheelHigher.temperature(fahrenheit));
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print("Back Flywheel Temperature: %d", (int) FlywheelLower.temperature(fahrenheit));
}

void toggleBrainInfo() {
  Brain.Screen.clearScreen();
  brainInfo = !brainInfo;
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
  LeftBack.spin(forward, leftSpeed, pct);
  RightFront.spin(forward, rightSpeed, pct);
  RightBack.spin(forward, rightSpeed, pct);
}

void stopDrive() {
  LeftFront.stop();
  LeftBack.stop();
  RightFront.stop();
  RightBack.stop();
}

void setDriveStopping(brakeType stopType) {
  LeftFront.setStopping(stopType);
  LeftBack.setStopping(stopType);
  RightFront.setStopping(stopType);
  RightBack.setStopping(stopType);
}

void  setDriveTimeout(float time) {
  LeftFront.setTimeout(time, seconds);
  LeftBack.setTimeout(time, seconds);
  RightFront.setTimeout(time, seconds);
  RightBack.setTimeout(time, seconds);
}

//Auton support functions
void move(float length, float speed, bool blocking = true) {
  float spinDistance = arcMeasure(length, wheelRadius) * (3.0 / 5);
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print(spinDistance);
  LeftFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  LeftBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  RightFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  RightBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, blocking);
}

void rotateOneSide(float angle, turnType direction, float initialSpeed = 100) {
  float length = arcLength(angle, turnRadius * 2);
  float spinDistance = (3.0 / 5) * arcMeasure(length, wheelRadius); //Adjusted for gear ratio
  float distanceSpun;
  float speed = initialSpeed;
  motor trackedMotor = direction == right ? LeftBack : RightBack; //Motor selection
  if (direction == right) {
    LeftFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
    LeftBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  } 
  if (direction == left) {
    RightFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
    RightBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  }
  float initialPosition = trackedMotor.position(degrees);
  while (!trackedMotor.isDone()) { //Slow down when approaching target
    distanceSpun = fabs(initialPosition - trackedMotor.position(degrees));
    speed = initialSpeed * ((spinDistance - distanceSpun) / spinDistance);
    if (direction == right) {
      LeftFront.setVelocity(speed, pct);
      LeftBack.setVelocity(speed, pct);
    }
    if (direction == left) {
      RightFront.setVelocity(speed, pct);
      RightBack.setVelocity(speed, pct);
    }
  }
  stopDrive();
}

void rotateBothSides(float angle, turnType direction, float initialSpeed = 100) {
  float length = arcLength(angle, turnRadius);
  float spinDistance = (3.0 / 5) * arcMeasure(length, wheelRadius);
  float speed = initialSpeed;
  float initialPosition = RightBack.position(degrees);
  float distanceSpun;
  LeftFront.spinFor(direction == left ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  LeftBack.spinFor(direction == left ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  RightFront.spinFor(direction == right ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  RightBack.spinFor(direction == right ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  while (!RightBack.isDone()) {
    distanceSpun = fabs(initialPosition - RightBack.position(degrees));
    speed = initialSpeed * ((spinDistance - distanceSpun) / spinDistance);
    Controller1.Screen.setCursor(3, 0);
    Controller1.Screen.print(speed);
    LeftFront.setVelocity(speed, pct);
    LeftBack.setVelocity(speed, pct);
    RightFront.setVelocity(speed, pct);
    RightBack.setVelocity(speed, pct);
  }
  stopDrive();
}

//Auton functions
void rightSimple() {
  setFlywheelSpeed(73);
  wait(0.5, seconds);
  rotateOneSide(-22, left, 30);
  wait(5, seconds);
  shoot();
  setFlywheelSpeed(70);
  wait(2, seconds);
  shoot();
}

void skills() {
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

void lowGoal() {
  startFlywheel();
  wait(5, seconds);
  shoot();
  wait(3, seconds);
  shoot();
}

void roller() {
  setDriveTimeout(5);
  move(1.5, 20);
  rotateRoller(360);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Indexer.set(false);
  Expander.set(false);
}

void autonomous(void) {
  Indexer.set(false);
  Expander.set(false);
  IntakeHigher.setStopping(coast);
  IntakeLower.setStopping(coast);
  setDriveStopping(hold);
  //rightSimple();
  //skills();
  //lowGoal();
  roller();
}

void usercontrol(void) {
  Controller1.Screen.clearScreen();
  FlywheelHigher.setStopping(coast);
  FlywheelLower.setStopping(coast);
  IntakeHigher.setStopping(coast);
  IntakeLower.setStopping(coast);
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
