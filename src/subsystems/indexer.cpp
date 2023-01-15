//Functions and values for indexer

#include "subsystems\indexer.h"

int startingPosition = 160;

void startIndexer() {
  Indexer.rotateFor(forward, startingPosition, degrees, 100, velocityUnits::pct, false);
}

void updateIndexer() {
  float indexerPosition = Indexer.rotation(degrees);
  int relativePosition = ((int) indexerPosition - startingPosition) % 360;
  if (Controller1.ButtonB.pressing()) {
    Indexer.spin(forward, 100, pct);
  } else if (indexerPosition > 160 && relativePosition > 20) {
    Indexer.spinFor(forward, 360 - relativePosition, degrees, 100, velocityUnits::pct);
  }
}

void shoot(bool blocking) {
  Indexer.rotateFor(forward, 360 , degrees, 100, velocityUnits::pct, blocking);
}