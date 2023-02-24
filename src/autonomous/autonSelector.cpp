//Functions involved in selecting the autonomous routine before a match

#include "autonomous\autonSelector.h"

int selectedAuton = 8;

void changeAuton() { //Auton selector
  if (selectedAuton >= 9) {
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
    autonDescription = "Spin roller";
    break;

    case 6:
    autonDescription = "Spin roller and preloads to low goal";
    break;

    case 7:
    autonDescription = "Skills with 2 rollers";
    break;

    case 8:
    autonDescription = "Spin non-driver-side roller";
    break;

    case 9:
    autonDescription = "Replay recorded auton";

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
      rightHalfWP();
      break;

      case 3:
      skills();
      break;

      case 4:
      lowGoal();
      break;

      case 5:
      roller();
      break;

      case 6:
      rollerLowGoal();
      break;

      case 7:
      skillsRoller();
      break;

      case 8:
      farSideRoller();

      case 9:
      replay();
    }
}