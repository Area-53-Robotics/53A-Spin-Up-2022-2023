//Functions involved in selecting the autonomous routine before a match

#include "autonomous\autonSelector.h"

int selectedAuton = 0;

void changeAuton() { //Auton selector
  if (selectedAuton >= 11) {
    selectedAuton = 0;
  } else {
    selectedAuton++;
  }
  printAutonDescription();
}

void printAutonDescription() {
  std::string autonDescription;
  switch (selectedAuton) {
    case 0:
    autonDescription = "None";
    break;

    case 1:
    autonDescription = "Testing";
    break;

    case 2:
    autonDescription = "Right side roller, preloads to high goal";
    break;

    case 3:
    autonDescription = "Skills";
    break;

    case 4:
    autonDescription = "Preloads to low goal";
    break;

    case 5:
    autonDescription = "Spin driver-side roller";
    break;

    case 6:
    autonDescription = "Close roller and preloads to low goal";
    break;

    case 7:
    autonDescription = "Skills with 2 rollers";
    break;

    case 8:
    autonDescription = "Spin non-driver-side roller";
    break;

    case 9:
    autonDescription = "Close roller and preloads to high goal";
    break;

    case 10:
    autonDescription = "Both rollers and preloads to high goal";
    break;

    case 11:
    autonDescription = "Replay recorded auton";
    break;

    default:
    autonDescription = "Index out of bounds";
    break;
  }
  Brain.Screen.setCursor(12, 1);
  Brain.Screen.clearLine();
  Brain.Screen.print("Auton: %s", autonDescription.c_str());
}

void runAuton() {
  switch (selectedAuton) {
      case 1:
      test();
      break;

      case 2:
      rightHalfWinPoint();
      break;

      case 3:
      skills();
      break;

      case 4:
      lowGoal();
      break;

      case 5:
      closeRoller();
      break;

      case 6:
      closeRollerLowGoal();
      break;

      case 7:
      skillsRoller();
      break;

      case 8:
      farRoller();
      break;

      case 9:
      leftHalfWinPoint();
      break;

      case 10:
      fullWinPoint();
      break;

      case 11:
      replay();
      break;
    }
}