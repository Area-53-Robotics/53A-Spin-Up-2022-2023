//Flywheel control functions

#include "subsystems\flywheel.h"

mutex controllerScreen;

int printFlywheelInfo() { //int because required for task
  //int cycleCount = 0;
  //Make sure line is clear before using
  while (1) {
    controllerScreen.lock();
    Controller1.Screen.setCursor(1, 0);
    Controller1.Screen.print("Motor speed: %.2f", Flywheel.velocity(rpm));
    /*if (FlywheelRamp.value()) { //Dashes indicate flywheel ramp is up
      cycleCount++;
      if (cycleCount == 1) {
        Controller1.Screen.setCursor(1, 0);
        Controller1.Screen.print("==================");
        Controller1.Screen.setCursor(3, 0);
        Controller1.Screen.print("==================");
      } else if (cycleCount == 3) {
        Controller1.Screen.clearLine(1);
        Controller1.Screen.clearLine(3);
      } else if (cycleCount == 4) {
        cycleCount = 0;
      }
    }*/
    controllerScreen.unlock();
    task::sleep(100);
  }
  return 0;
}

void setFlywheelSpeed(float speed, velocityUnits units) {
  Flywheel.spin(forward, speed, units);
  //FlywheelLower.spin(forward, speed, units);
}

void changeFlywheelSpeed(float speedDifference, velocityUnits units) {
  float speed = Flywheel.velocity(units);
  setFlywheelSpeed(speed + speedDifference, units);
}

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
  setFlywheelSpeed(450, rpm);
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