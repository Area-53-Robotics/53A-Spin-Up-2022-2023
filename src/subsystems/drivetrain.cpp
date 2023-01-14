//Functions to configure drivetrain and operate it during driver control

#include "subsystems\drivetrain.h"

float driveCurve(float joystickPosition) { //Exponential function with adjustable constants to change curve
  float a = 3.53231;
  float b = 1.03442;
  float c = -4.18356;
  return fabs(joystickPosition) >= 5 ? (fabs(joystickPosition) / joystickPosition) * ((a * pow(b, fabs(joystickPosition))) + c) : 0;
}

void updateDriveSpeed() {
  float leftSpeed = driveCurve(Controller1.Axis3.position(percent));
  float rightSpeed = driveCurve(Controller1.Axis2.position(percent));
  /* Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print("%4.f, %4.f", leftSpeed, rightSpeed); */
  LeftFront.spin(forward, leftSpeed, pct);
  LeftTop.spin(forward, leftSpeed, pct);
  LeftBack.spin(forward, leftSpeed, pct);
  RightFront.spin(forward, rightSpeed, pct);
  RightTop.spin(forward, rightSpeed, pct);
  RightBack.spin(forward, rightSpeed, pct);
}

void stopDrive() {
  LeftFront.stop();
  LeftTop.stop();
  LeftBack.stop();
  RightFront.stop();
  RightTop.stop();
  RightBack.stop();
}

void setDriveStopping(brakeType stopType) {
  LeftFront.setStopping(stopType);
  LeftTop.setStopping(stopType);
  LeftBack.setStopping(stopType);
  RightFront.setStopping(stopType);
  RightTop.setStopping(stopType);
  RightBack.setStopping(stopType);
}

void  setDriveTimeout(float time) {
  LeftFront.setTimeout(time, seconds);
  LeftTop.setTimeout(time, seconds);
  LeftBack.setTimeout(time, seconds);
  RightFront.setTimeout(time, seconds);
  RightTop.setTimeout(time, seconds);
  RightBack.setTimeout(time, seconds);
}