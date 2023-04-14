//Autonomous routines, called in the auton selector

#include "autonomous\autonPrograms.h"

void test() { //1
  rotate(90, left);
  wait(1, seconds);
  rotate(90, right);
}

void rightHalfWinPoint() { //2
  InertialSensor.resetRotation();
  setFlywheelSpeed(450);
  farRoller();
  wait(1, sec);
  move(-5, 50);
  spinIntake(forward);
  rotate(-73, right, 0.5);
  wait(2, sec);
  shoot();
  setFlywheelSpeed(470);
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
  setFlywheelSpeed(425);
  setDriveTimeout(5);
  move(1.5, 20);
  rotateRoller(-180); //Get starting roller
  move(-10, 50);
  rotate(90, right, 0.5); //Go toward other roller in starting corner
  spinIntake(forward); //Pick up disk that's in the way
  move(26, 20);
  stopIntake(); //Don't spin roller too early
  move(2, 20);
  rotateRoller(180); //Get other roller in starting corner
  move(-25, 40);
  spinIntake(forward); //Make sure earlier disk finished intaking
  rotate(100, right); //Turn to goal on starting side
  repeatShot(); //Shoot volley of 3
  setFlywheelSpeed(400);
  rotate(180, right);
  stopIntake();
  move(10, 40); //Knock down 3-stack
  move(-10, 60);
  spinIntake(forward);
  move(30, 20); //Pick up 3-stack behind shooting position
  rotate(10, left);
  repeatShot(); //Shoot in other goal from before (slightly closer and less full)
  rotate(0, right);
  move(18, 50); //Get back to auton line
  rotate(45, right); //Turn to center
  expand();
  wait(2, seconds);
  move(30, 50);
}

void farRoller() { //8
  setDriveTimeout(2);
  setIntakeTimeout(3);
  move(-18, 30);
  rotate(90, left, 2);
  move(4.5, 20);
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