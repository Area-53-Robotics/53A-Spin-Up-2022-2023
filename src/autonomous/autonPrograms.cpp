//Autonomous routines, called in the auton selector

#include "autonomous\autonPrograms.h"

void test() { //1
  move(24, 50);
  //rotateBothSides(45, right, 13);
  /* wait(1, seconds);
  rotateBothSides(90, right, 20);
  wait(1, seconds);
  rotateOneSide(90, left, 20);
  wait(1, seconds);
  rotateOneSide(90, right, 20);
  wait(1, seconds); */
}

void rightHalfWP() { //2
  setFlywheelSpeed(475);
  move(24, 50);
  wait(100, msec);
  rotateBothSides(45, right, 13);
  move(18, 50);
  wait(100, msec);
  rotateBothSides(45, right, 13);
  setDriveTimeout(3);
  move(12, 20);
  rotateRoller(-90);
  move(-12, 50);
  wait(100, msec);
  rotateBothSides(10, right, 5);
  shoot();
  setFlywheelSpeed(480);
  wait(2, seconds);
  shoot();
}

void skills() { //3
  closestFlywheel();
  setDriveTimeout(5);
  move(1.5, 20);
  rotateRoller(-180);
  move(-50, 100);
  rotateBothSides(25, left, 10);
  shoot();
  wait(2, seconds);
  shoot();
  wait(1, seconds);
  rotateBothSides(100, right, 40, true, 3);
  expand();
}

void lowGoal() { //4
  setFlywheelSpeed(200);
  wait(5, seconds);
  shoot();
  wait(3, seconds);
  shoot();
}

void roller() { //5
  setDriveTimeout(5);
  move(1.5, 20);
  rotateRoller(-90);
}

void rollerLowGoal() { //6
  setFlywheelSpeed(300);
  roller();
  move(-2, 50);
  wait(200, msec);
  rotateBothSides(90, left);
  wait(2, seconds);
  shoot();
  wait(2, seconds);
  shoot();
}

void skillsRoller() { //7
  setDriveTimeout(8);
  move(1.5, 20);
  rotateRoller(-180, true);
  
  /*move(-24, 50);
  rotateBothSides(90, right);
  move(36, 30);
  rotateRoller(-180, true);
  move(-12, 50);
  rotateBothSides(135, right);
  expand();
  move(150, 30);*/
}

void farSideRoller() {
  move(-16, 30);
  rotateBothSides(90, left, 25, true, 2);
  move(5, 20);
  rotateRoller(-90);
}