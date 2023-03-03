//Flywheel control functions

#include "subsystems\flywheel.h"

mutex controllerScreen;
PID flywheelSpeedController(getFlywheelSpeed, 0, 0.05, 0.0001);

int printFlywheelInfo() { //int because required for task
  int cycleCount = 0;
  //Make sure line is clear before using
  while (1) {
    controllerScreen.lock();
    Controller1.Screen.setCursor(2, 0);
    Controller1.Screen.print("Motor speed: %.2f", getFlywheelSpeed());
    if (FlywheelRamp.value()) { //Dashes indicate flywheel ramp is up
      cycleCount++;
      if (cycleCount == 1) {
        Controller1.Screen.setCursor(1, 0);
        Controller1.Screen.print("==================");
        Controller1.Screen.setCursor(3, 0);
        Controller1.Screen.print("==================");
      } else if (cycleCount == 3) {
        //Controller1.Screen.clearLine(1);
        Controller1.Screen.clearLine(3);
      } else if (cycleCount == 4) {
        cycleCount = 0;
      }
    }
    controllerScreen.unlock();
    task::sleep(100);
  }
  return 0;
}

int updateFlywheelSpeed() {
  float flywheelVoltage;
  while(1) {
    flywheelVoltage = flywheelSpeedController.update();
    if (flywheelVoltage > 14.4) {
      flywheelVoltage = 14.4;
    } else if (flywheelVoltage < 0) {
      flywheelVoltage = 0;
    }
    /* controllerScreen.lock();
    Controller1.Screen.setCursor(1, 0);
    Controller1.Screen.print("Voltage: %3.2f", flywheelVoltage);
    controllerScreen.unlock(); */
    Flywheel.spin(forward, flywheelVoltage, volt);
    task::sleep(50);
  }
  return 0;
}

float getFlywheelSpeed() {
  return FlywheelSensor.velocity(rpm) / 5;
  //return Flywheel.velocity(rpm);
}

void setFlywheelSpeed(float speed, velocityUnits units) {
  //flywheelSpeedController.set(speed);
  Flywheel.spin(forward, speed, units);
  //FlywheelLower.spin(forward, speed, units);
}

void changeFlywheelSpeed(float speedDifference, velocityUnits units) {
  float speed = Flywheel.velocity(units);
  setFlywheelSpeed(speed + speedDifference, units);
}

void stopFlywheel() {
  //flywheelSpeedController.set(0);
  Flywheel.stop(coast);
  //FlywheelLower.stop(coast);
}