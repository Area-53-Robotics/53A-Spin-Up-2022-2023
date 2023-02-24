//Too many functions that control the flywheel, all called by buttons

#include "subsystems\flywheelButtons.h"

void incrementFlywheel() {
  changeFlywheelSpeed(10, rpm);
}

void decrementFlywheel() {
  changeFlywheelSpeed(-10, rpm);
}

void stopFlywheel() {
  Flywheel.stop(coast);
  //FlywheelLower.stop(coast);
}

void closestFlywheel() { //To shoot from just outside close low goal (at its corner)
  setFlywheelSpeed(350, rpm);
}

void rollerFlywheel() { //To shoot from roller
  setFlywheelSpeed(385, rpm);
}

void lowGoalFlywheel() { //To shoot from just inside far low goal, at corner
  setFlywheelSpeed(500, rpm);
}

void maxFlywheel() {
  setFlywheelSpeed(100, velocityUnits::pct);
}

void toggleFlywheelRamp() {
  FlywheelRamp.set(!FlywheelRamp.value());
  Controller1.Screen.clearLine(1);
  Controller1.Screen.clearLine(3);
}