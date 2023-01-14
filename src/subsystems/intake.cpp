//Control functions for systems using the intake motors, currently intake and roller

#include "subsystems\intake.h"

bool intakePower = false;
bool intakeDirection = true;

//Intake
void toggleIntake() {
  intakePower = !intakePower;
}

void changeIntakeDirection() {
  intakeDirection = !intakeDirection;
}

void updateIntake() {
  Intake.spin(intakeDirection ? forward : reverse, intakePower ? 100 : 0, pct);
}

//Roller
void rotateRoller(float angle, bool blocking) {
  Intake.spinFor(forward, angle * (35 / 3), degrees, 100, velocityUnits::pct, blocking);
  //IntakeLower.spinFor(forward, angle, degrees, 100, velocityUnits::pct, false);
}