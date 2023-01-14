//Functions controlling the brain screen and functions run by pressing it

#include "brainScreen.h"

bool calibrated = false;

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

bool isCalibrated() {
  return calibrated;
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