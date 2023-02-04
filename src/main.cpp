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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Indexer.set(false);
  Expander.set(false);
  FlywheelRamp.set(false);
  drawPreautonMenu();
  Brain.Screen.pressed(brainPressEvent);
}

void autonomous(void) {
  Controller1.Screen.clearScreen();
  Indexer.set(false);
  Expander.set(false);
  FlywheelRamp.set(false);
  Intake.setStopping(coast);
  Roller.setStopping(coast);
  setDriveStopping(hold);
  runAuton();
  if (!isCalibrated()) {
    calibrate();
  }
}

void usercontrol(void) {
  Controller1.Screen.clearScreen();
  Flywheel.setStopping(coast);
  //FlywheelLower.setStopping(coast);
  Intake.setStopping(coast);
  Roller.setStopping(coast);
  Indexer.set(false);
  Expander.set(false);
  FlywheelRamp.set(false);
  closestFlywheel();

  //Button callbacks
  Controller1.ButtonDown.pressed(closestFlywheel);
  Controller1.ButtonX.pressed(stopFlywheel);
  //Controller1.ButtonY.pressed(toggleRecording);
  Controller1.ButtonA.pressed(toggleFlywheelRamp);
  Controller1.ButtonB.pressed(shoot);
  Controller1.ButtonRight.pressed(decrementFlywheel);
  Controller1.ButtonUp.pressed(incrementFlywheel);
  Controller1.ButtonLeft.pressed(rollerFlywheel);
  task flyWheelSpeed(printFlywheelSpeed);
  setDriveStopping(brake);
  //startIndexer();
  while (true) {
    updateDriveSpeed();
    updateIntake();
    checkExpansion();
    //updateIndexer();
    
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
