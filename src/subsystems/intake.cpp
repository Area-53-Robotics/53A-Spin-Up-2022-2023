//Control functions for systems using the intake motors, currently intake and roller

#include "subsystems\intake.h"

char intakeDirection = '0';
const float rollerWheelRadius = 2;
const float rollerRadius = 2.375 / 2;

//Intake
void spinIntake(directionType direction) {
  Intake.spin(direction, 100, pct);
  Roller.spin(direction, 100, pct);
}

void stopIntake() {
  Intake.stop();
  Roller.stop();
  }

void setIntakeForward() {
  intakeDirection = intakeDirection == '+' ? '0' : '+';
}

void setIntakeReverse() {
  intakeDirection = intakeDirection == '-' ? '0' : '-';
}

void updateIntake() { //What if you press a toggle button while holding a hold button?
  if (Controller1.ButtonL1.pressing()) { //Make it remember which one started holding first
    spinIntake(forward);
  } else if (Controller1.ButtonR1.pressing()) {
    spinIntake(reverse);
  } else if (intakeDirection == '+') {
    spinIntake(forward);
  } else if (intakeDirection == '-') {
    spinIntake(reverse);
  } else {
    stopIntake();
  }
}

//Roller
void rotateRoller(float rollerAngle, bool blocking) {
  float wheelAngle = rollerAngle * (rollerRadius / rollerWheelRadius);
  Intake.spinFor(forward, wheelAngle * 6, degrees, 100, velocityUnits::pct, false);
  Roller.spinFor(forward, wheelAngle, degrees, 100, velocityUnits::pct, blocking);
}

void setIntakeTimeout(float time) {
  Intake.setTimeout(time, seconds);
  Roller.setTimeout(time, seconds);
}