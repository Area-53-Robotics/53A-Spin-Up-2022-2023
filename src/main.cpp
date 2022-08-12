/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Benjamin Ruby                                             */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  53A's main competition program for the 2022-2023 season   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FlywheelFront        motor         1               
// Controller1          controller                    
// LeftFront            motor         11              
// LeftTop              motor         15              
// LeftBack             motor         3               
// RightBack            motor         16              
// RightTop             motor         19              
// RightFront           motor         20              
// Intake               motor         10              
// FlywheelBack         motor         2               
// Indexer              digital_out   A               
// Expander             digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

//Global variables
float J2;
float J3;
bool intakeMode;
bool brainInfo = false;

//Functions
int printFlywheelSpeed() {
  //Make sure line 3 is clear before using
  while (1) {
    Controller1.Screen.setCursor(3, 0);
    Controller1.Screen.print("Actual speed: %.2f", FlywheelFront.velocity(rpm));
    task::sleep(200);
  }
  return 0;
}

int startFlyWheelInt() {
  Controller1.Screen.clearScreen();
  float maximum = 0;
  for (int speed = FlywheelFront.velocity(pct); speed <= 100; speed++) {
    FlywheelFront.spin(fwd, speed, pct);
    FlywheelBack.spin(fwd, speed, pct);
    if (FlywheelFront.velocity(rpm) > maximum) {
      maximum = FlywheelFront.velocity(rpm);
    }
    Controller1.Screen.setCursor(1, 0);
    Controller1.Screen.print("Maximum speed: %.2f", maximum);
    Controller1.Screen.setCursor(2, 0);
    Controller1.Screen.print("Intended speed: %4d", speed);
    task::sleep(200);
    if (Controller1.ButtonA.pressing()) {
      Controller1.Screen.setCursor(1, 0);
      Controller1.Screen.clearLine();
      Controller1.Screen.print("Holding current speed");
      return 0;
    }
  }
  return 1;
}

void startFlyWheel() {
  task flyWheelTask(startFlyWheelInt);
}

void stopFlyWheel() {
  Controller1.Screen.clearScreen();
  for (int speed = FlywheelFront.velocity(percent); speed >= 0; speed--) {
    FlywheelFront.spin(fwd, speed, pct);
    FlywheelBack.spin(fwd, speed, pct);
    Controller1.Screen.setCursor(2, 0);
    Controller1.Screen.print("Intended speed: %3d", speed);
    wait(200, msec);
    if (Controller1.ButtonA.pressing()) {
      return;
    }
  }
  FlywheelFront.stop();
  FlywheelBack.stop();
}

void stopFlywheelNow() {
  FlywheelFront.stop(coast);
  FlywheelBack.stop(coast);
}

void shoot() {
  Indexer.set(true);
  wait(0.2,sec);
  Indexer.set(false);
}

void expand() {
  Expander.set(true);
}

void updateDriveSpeed() {
  J2 = Controller1.Axis2.position(percent);
  J3 = Controller1.Axis3.position(percent);
  LeftFront.spin(forward, J3, pct);
  LeftTop.spin(forward, J3, pct);
  LeftBack.spin(forward, J3, pct);
  RightFront.spin(forward, J2, pct);
  RightTop.spin(forward, J2, pct);
  RightBack.spin(forward, J2, pct);
}

void printBrainInfo() {
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Front Flywheel Temperature: %d", (int) FlywheelFront.temperature(fahrenheit));
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print("Back Flywheel Temperature: %d", (int) FlywheelBack.temperature(fahrenheit));
}

void switchIntake() {
  intakeMode = !intakeMode;
}

void toggleBrainInfo() {
  Brain.Screen.clearScreen();
  brainInfo = !brainInfo;
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

void autonomous(void) {
}

void usercontrol(void) {
  FlywheelFront.setStopping(coast);
  FlywheelBack.setStopping(coast);
  Controller1.ButtonR1.pressed(startFlyWheel);
  Controller1.ButtonR2.pressed(stopFlyWheel);
  Controller1.ButtonL1.pressed(switchIntake);
  Controller1.ButtonB.pressed(shoot);
  Controller1.ButtonLeft.pressed(expand);
  Controller1.ButtonX.pressed(stopFlywheelNow);
  Brain.Screen.pressed(toggleBrainInfo);
  task flyWheelSpeed(printFlywheelSpeed);
  while (true) {
    updateDriveSpeed();
    if (brainInfo) {
      printBrainInfo();
    }
    Intake.spin(fwd, intakeMode ? 100 : 25, pct);
    
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
