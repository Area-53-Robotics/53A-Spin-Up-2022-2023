//Functions and values for indexer

#include "subsystems\indexer.h"

//int startingPosition = 160;

void startIndexer() {
  //Indexer.rotateFor(forward, startingPosition, degrees, 100, velocityUnits::pct, false);
}

void updateIndexer() {
  /*float indexerPosition = Indexer.rotation(degrees);
  int relativePosition = ((int) indexerPosition - startingPosition) % 360;
  if (Controller1.ButtonB.pressing()) {
    Indexer.spin(forward, 100, pct);
  } else if (indexerPosition > 160 && relativePosition > 20) {
    Indexer.spinFor(forward, 360 - relativePosition, degrees, 100, velocityUnits::pct);
  }*/
}

void shoot() {
  Indexer.rotateTo(70, degrees, 100, velocityUnits::pct); //90, 60, 55, 40, 50, 65, 75, 70
  Indexer.rotateTo(0, degrees, 100, velocityUnits::pct);
  if (Controller1.ButtonB.pressing()) {
    wait(0.09, sec); //0.1, 0.08, 0.09
    shoot();
  }
  /*Indexer.set(true);
  wait(0.03, sec);
  Indexer.set(false);*/
}