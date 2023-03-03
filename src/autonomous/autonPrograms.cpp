//Autonomous routines, called in the auton selector

#include "autonomous\autonPrograms.h"

void test() { //1
  rotate(90, left);
  wait(1, seconds);
  rotate(90, right);
}

void rightHalfWinPoint() { //2
  InertialSensor.resetRotation();
  setFlywheelSpeed(470);
  farRoller();
  wait(1, sec);
  move(-5, 50);
  spinIntake(forward);
  rotate(-70, right, 0.5);
  wait(2, sec);
  shoot();
  wait(3, sec);
  shoot();
}

void skills() { //3
  closestFlywheel();
  setDriveTimeout(5);
  move(1.5, 20);
  rotateRoller(-180);
  move(-50, 100);
  rotate(25, left);
  shoot();
  wait(2, seconds);
  shoot();
  wait(1, seconds);
  rotate(100, right, 3);
  expand();
}

void lowGoal() { //4
  setFlywheelSpeed(200);
  wait(5, seconds);
  shoot();
  wait(3, seconds);
  shoot();
}

void closeRoller() { //5
  setDriveTimeout(5);
  move(1.5, 20);
  rotateRoller(-90);
}

void closeRollerLowGoal() { //6
  setFlywheelSpeed(300);
  closeRoller();
  wait(100, msec);
  move(-2, 50);
  wait(200, msec);
  rotate(90, right);
  wait(2, seconds);
  shoot();
  wait(2, seconds);
  shoot();
}

void skillsRoller() { //7
  setDriveTimeout(8);
  move(1.5, 20);
  rotateRoller(-180, true);
  
}

void farRoller() { //8
setDriveTimeout(2);
  move(-16, 30);
  rotate(90, left, 2);
  move(5, 20);
  rotateRoller(-90);
}

void leftHalfWinPoint() { //9
  setFlywheelSpeed(450);
  closeRoller();
  wait(1, sec);
  move(-5, 50);
  rotate(10, right, 0.5);
  shoot();
  wait(1, sec);
  shoot();
}

void fullWinPoint() { //10
  rightHalfWinPoint();
  rotate(120, left, 0.5);
  setDriveTimeout(10);
  move(136, 100);
  setDriveTimeout(2);
  rotate(45, left, 1);
  move(8, 30);
  rotateRoller(-90);
}

void replay() { //11
  char velocity[8] = "0";
  std::ifstream autonFile("recordedAuton.txt");
  while(!autonFile.is_open()) {
    wait(20, msec);
  }
  while (1) {
    for (motor recordedMotor : recordedMotors) {
      autonFile.getline(velocity, 8);
      recordedMotor.spin(forward, atof(velocity), rpm);
    }
    wait(20, msec);
  }
  autonFile.close();
  while(autonFile.is_open()) {
    wait(20, msec);
  }
}