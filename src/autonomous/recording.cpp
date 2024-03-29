//Records driver movements for playback in auton

#include "autonomous\recording.h"

std::ofstream autonFile;
bool recording = false;

int record() {
  while (!autonFile.is_open()) {
    task::sleep(20);
  }
  Controller1.Screen.clearLine(1);
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print("File open");
  while (recording) {
    for (motor recordedMotor : recordedMotors) {
      autonFile << recordedMotor.velocity(rpm);
      autonFile << "\n";
    }
    task::sleep(20);
  }
  autonFile.close();
  Controller1.Screen.clearLine(1);
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print("Closing file...");
  while (autonFile.is_open()) {
    task::sleep(20);
  }
  Controller1.Screen.clearLine(1);
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print("File closed");
  return 1;
}

void toggleRecording() {
  if (!recording) {
    recording = true;
    Controller1.Screen.clearLine(1);
    Controller1.Screen.setCursor(1, 0);
    Controller1.Screen.print("Started recording movement");
    autonFile.open("recordedAuton.txt");
    task autonRecording(record);
  } else {
    recording = false;
  }
}