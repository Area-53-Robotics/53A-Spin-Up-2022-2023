/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Benjamin Ruby                                             */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  53A's main competition program for the 2022-2023 season   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

//Global variables
bool brainInfo = false;
bool calibrated = false;

//Info functions
void printMotorTemperature() {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Left front: %.f", LeftFront.temperature());
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Left top: %.f", LeftTop.temperature());
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Left back: %.f", LeftBack.temperature());
  Brain.Screen.setCursor(4, 1);
  Brain.Screen.print("Right front: %.f", RightFront.temperature());
  Brain.Screen.setCursor(5, 1);
  Brain.Screen.print("Right top: %.f", RightTop.temperature());
  Brain.Screen.setCursor(6, 1);
  Brain.Screen.print("Right back: %.f", RightBack.temperature());
}

//Miscellaneous functions
void calibrate() {
  InertialSensor.startCalibration();
  Brain.Screen.setCursor(12, 1);
  int dots = 0;
  while (InertialSensor.isCalibrating()) {
    Brain.Screen.clearLine();
    Brain.Screen.print("Inertial sensor calibrating");
    for (int dot = 0; dot <= dots - 1; dot++) {
      Brain.Screen.print(".");
    }
    dots = dots >= 3 ? 0 : dots + 1;
    wait(200, msec);
  }
  Brain.Screen.clearLine();
  Brain.Screen.print("Calibration complete!");
  calibrated = true;
}

void drawPreautonMenu() {
  color background = color(0, 50, 0);
  Brain.Screen.clearScreen(background);
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(background);
  Brain.Screen.drawLine(240, 0, 240, 216);
  Brain.Screen.drawLine(0, 120, 480, 120);
  Brain.Screen.drawLine(0, 216, 480, 216);
  Brain.Screen.setCursor(3, 2);
  Brain.Screen.print("Calibrate inertial");
  Brain.Screen.setCursor(4, 2);
  Brain.Screen.print("sensor");
  Brain.Screen.setCursor(8, 2);
  Brain.Screen.print("Print drive");
  Brain.Screen.setCursor(9, 2);
  Brain.Screen.print("motor temperatures");
  Brain.Screen.setCursor(3, 30);
  Brain.Screen.print("Switch auton");
  Brain.Screen.setCursor(9, 30);
  Brain.Screen.print("Redraw menu");
}

void brainPressEvent() {
  if (Brain.Screen.xPosition() <= 240) {
    if (Brain.Screen.yPosition() <= 120) {
      calibrate();
    } else {
    printMotorTemperature();
    }
  } else {
    if (Brain.Screen.yPosition() <= 120) {
      changeAuton();
    } else {
    drawPreautonMenu();
    }
  }
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Indexer.set(false);
  Expander.set(false);
  drawPreautonMenu();
  Brain.Screen.pressed(brainPressEvent);
}

void autonomous(void) {
  Controller1.Screen.clearScreen();
  Indexer.set(false);
  Expander.set(false);
  Intake.setStopping(coast);
  //IntakeLower.setStopping(coast);
  setDriveStopping(hold);
  if (!calibrated) {
    calibrate();
  }
}

void usercontrol(void) {
  Controller1.Screen.clearScreen();
  Flywheel.setStopping(coast);
  //FlywheelLower.setStopping(coast);
  Intake.setStopping(coast);
  //IntakeLower.setStopping(coast);
  Indexer.set(false);
  Expander.set(false);

  //Button callbacks
  Controller1.ButtonL1.pressed(toggleIntake);
  Controller1.ButtonR1.pressed(changeIntakeDirection);
  Controller1.ButtonL2.pressed(closestFlywheel);
  Controller1.ButtonR2.pressed(rollerFlywheel);
  Controller1.ButtonB.pressed(shoot);
  Controller1.ButtonX.pressed(stopFlywheel);
  Controller1.ButtonRight.pressed(closestFlywheel);
  Controller1.ButtonUp.pressed(rollerFlywheel);
  task flyWheelSpeed(printFlywheelSpeed);
  setDriveStopping(brake);
  while (true) {
    updateDriveSpeed();
    updateIntake();
    checkExpansion();
    
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
