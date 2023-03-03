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

void rotate(float angle, turnType direction, float margin, bool oneSide) {
  //InertialSensor.resetRotation();
  PID turnSpeedController = PID(getRotation, direction == right ? angle : angle * -1, 0.4);
  float turnSpeed;
  do {
    turnSpeed = turnSpeedController.update();
    Controller1.Screen.setCursor(0, 1);
    Controller1.Screen.print("Speed: %3.2f", turnSpeed);
    if (!oneSide) {
      LeftFront.spin(forward, turnSpeed, pct);
      LeftBack.spin(forward, turnSpeed, pct);
      RightFront.spin(reverse, turnSpeed, pct);
      RightBack.spin(reverse, turnSpeed, pct);
    } else {
      if (direction == right) {
        LeftFront.spin(forward, turnSpeed, pct);
        LeftBack.spin(forward, turnSpeed, pct);
      } else {
        RightFront.spin(forward, turnSpeed, pct);
        RightBack.spin(forward, turnSpeed, pct);
      }
    }
  } while (fabs(turnSpeed) > margin);
  LeftFront.stop();
  LeftBack.stop();
  RightFront.stop();
  RightBack.stop();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.clearLine();
  Controller1.Screen.print("Done!");
}