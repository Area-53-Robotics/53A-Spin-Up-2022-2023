//Autonomous routines, called in the auton selector

#include "autonomous\autonPrograms.h"

void test() { //1
  rotate(90, left);
  wait(1, seconds);
  rotate(90, right);
}

void rightHalfWP() { //2
  setFlywheelSpeed(475);
  move(24, 50);
  wait(100, msec);
  rotate(45, right);
  move(18, 50);
  wait(100, msec);
  rotate(45, right);
  setDriveTimeout(3);
  move(12, 20);
  rotateRoller(-90);
  move(-12, 50);
  wait(100, msec);
  rotate(10, right);
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
  rotate(90, left);
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
  rotate(90, left, 2);
  move(5, 20);
  rotateRoller(-90);
}