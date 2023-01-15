//Flywheel control functions

#include "subsystems\flywheel.h"

int printFlywheelSpeed() { //int because required for task
  //Make sure line 3 is clear before using
  while (1) {
    Controller1.Screen.setCursor(2, 0);
    Controller1.Screen.print("Motor speed: %.2f", Flywheel.velocity(rpm));
    task::sleep(100);
  }
  return 0;
}

void setFlywheelSpeed(float speed, velocityUnits units) {
  Flywheel.spin(forward, speed, units);
  //FlywheelLower.spin(forward, speed, units);
}

void changeFlywheelSpeed(float speedDifference) {
  float speed = Flywheel.velocity(percent);
  setFlywheelSpeed(speed + speedDifference);
}

void stopFlywheel() {
  Flywheel.stop(coast);
  //FlywheelLower.stop(coast);
}

void closestFlywheel() { //To shoot from just outside low goal (at its corner)
  setFlywheelSpeed(350, rpm);
}

void rollerFlywheel() { //To shoot from roller
  setFlywheelSpeed(425, rpm);
}