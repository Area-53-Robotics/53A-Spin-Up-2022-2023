//Functions for autonomous movement relative to current position

#include "autonomous\autonMovement.h"

const float wheelRadius = 3.25 / 2;
const float driveWidth = 13;
const float driveLength = 12;
const float turnRadius = hypotf(driveWidth, driveLength) / 2;

void move(float length, float speed, bool blocking) { //Drive in a straight line
  float spinDistance = arcMeasure(length, wheelRadius) * (3.0 / 5);
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print(spinDistance);
  LeftFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  //LeftTop.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  LeftBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  RightFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  //RightTop.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
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
    //LeftTop.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
    LeftBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  } 
  if (direction == left) {
    RightFront.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
    //RightTop.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
    RightBack.spinFor(spinDistance, degrees, speed, velocityUnits::pct, false);
  }
  float initialPosition = trackedMotor.position(degrees);
  while (!trackedMotor.isDone()) { //Slow down when approaching target
    distanceSpun = fabs(initialPosition - trackedMotor.position(degrees));
    speed = initialSpeed * ((spinDistance - distanceSpun) / spinDistance);
    if (direction == right) {
      LeftFront.setVelocity(speed, pct);
      //LeftTop.setVelocity(speed, pct);
      LeftBack.setVelocity(speed, pct);
    }
    if (direction == left) {
      RightFront.setVelocity(speed, pct);
      //RightTop.setVelocity(speed, pct);
      RightBack.setVelocity(speed, pct);
    }
  }
  stopDrive();
}

void rotateBothSidesEncoder(float angle, turnType direction, float initialSpeed, float margin) {
  float length = arcLength(angle, turnRadius);
  float spinDistance = (3.0 / 5) * arcMeasure(length, wheelRadius);
  float speed = initialSpeed;
  float initialPosition = RightBack.position(degrees);
  float distanceSpun;
  LeftFront.spinFor(direction == left ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  //LeftTop.spinFor(direction == left ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  LeftBack.spinFor(direction == left ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  RightFront.spinFor(direction == right ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  //RightTop.spinFor(direction == right ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  RightBack.spinFor(direction == right ? reverse : forward, spinDistance, degrees, speed, velocityUnits::pct, false);
  while (!RightBack.isDone()) {
    distanceSpun = fabs(initialPosition - RightBack.position(degrees));
    speed = initialSpeed * ((spinDistance - distanceSpun) / spinDistance);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(speed);
    LeftFront.setVelocity(speed, pct);
    //LeftTop.setVelocity(speed, pct);
    LeftBack.setVelocity(speed, pct);
    RightFront.setVelocity(speed, pct);
    //RightTop.setVelocity(speed, pct);
    RightBack.setVelocity(speed, pct);
  }
  stopDrive();
}

void rotateOneSideInertial(float angle, turnType direction, float initialSpeed) {
  float speed = initialSpeed;
  float currentAngle = 0;
  InertialSensor.resetRotation();
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.clearLine(3);
  Controller1.Screen.print(fabs(angle - currentAngle));
  while (fabs(angle - currentAngle) > 1) {
    currentAngle = InertialSensor.angle();
    speed = initialSpeed * ((angle - currentAngle) / angle);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(speed);
    if (direction == right) {
      LeftFront.spin(forward, speed, pct);
      //LeftTop.spin(forward, speed, pct);
      LeftBack.spin(forward, speed, pct);
    }
    if (direction == left) {
      RightFront.spin(forward, speed, pct);
      //RightTop.spin(forward, speed, pct);
      RightBack.spin(forward, speed, pct);
    }
  }
  stopDrive();
}

void rotateBothSidesInertial(float angle, turnType direction, float initialSpeed, float margin) {
  float speed = initialSpeed;
  float currentAngle = 0;
  float proportionalError;
  InertialSensor.resetRotation();
  Controller1.Screen.clearLine(3);
  while (fabs(angle - currentAngle) > margin) {
    currentAngle = fabs(InertialSensor.rotation());
    proportionalError = (angle - currentAngle) / angle;
    speed = initialSpeed * proportionalError;
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(currentAngle);
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print(angle - currentAngle);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(speed);
    LeftFront.spin(direction == right ? forward : reverse, speed, pct);
    //LeftTop.spin(direction == right ? forward : reverse, speed, pct);
    LeftBack.spin(direction == right ? forward : reverse, speed, pct);
    RightFront.spin(direction == left ? forward : reverse, speed, pct);
    //RightTop.spin(direction == left ? forward : reverse, speed, pct);
    RightBack.spin(direction == left ? forward : reverse, speed, pct);
  }
  stopDrive();
}

void rotateOneSide(float angle, turnType direction, float initialSpeed, bool sensor) {
  if (sensor) {
    rotateOneSideInertial(angle, direction, initialSpeed);
  } else {
    rotateOneSideEncoder(angle, direction, initialSpeed);
  }
}

void rotateBothSides(float angle, turnType direction, float initialSpeed, bool sensor, float margin) {
  if (sensor) {
    rotateBothSidesInertial(angle, direction, initialSpeed, margin);
  } else {
    rotateBothSidesEncoder(angle, direction, initialSpeed, margin);
  }
}