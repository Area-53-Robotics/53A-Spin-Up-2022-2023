//Control functions for systems using the intake motors, currently intake and roller

#include "subsystems\intake.h"

char intakeDirection = '0';

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
void rotateRoller(float angle, bool blocking) {
  Intake.spinFor(forward, angle * 6, degrees, 100, velocityUnits::pct, false);
  Roller.spinFor(forward, angle, degrees, 100, velocityUnits::pct, blocking);
}