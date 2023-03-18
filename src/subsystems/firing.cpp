//Functions and values related to shooting

#include "subsystems\firing.h"

//int startingPosition = 160;
float delay = 0.11;
bool shooting = false;

void startIndexer() {
  //Indexer.rotateFor(forward, startingPosition, degrees, 100, velocityUnits::pct, false);
}

void updateIndexer() {
  if (Controller1.ButtonR2.pressing()) {
    Indexer.spin(forward, 100, pct);
  } else if (!shooting) {
    Indexer.stop();
  }
}

void increaseDelay() {
  delay += 0.01;
  printDelay();
}

void decreaseDelay() {
  delay -= 0.01;
  printDelay();
}

void printDelay() {
  controllerScreen.lock();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print("Indexer delay: %4.2f s", delay);
  controllerScreen.unlock();
}

void shoot() {
  shooting = true;
  if (!CompressionBar.value()) {
    CompressionBar.set(true);
    wait(0.03, sec);
  }
  Indexer.rotateFor(forward, 720, degrees, 100, velocityUnits::pct);
  CompressionBar.set(false);
  shooting = false;
}

void toggleCompression() {
  CompressionBar.set(!CompressionBar.value());
}

void releaseIndexer() {
  Indexer.stop(coast);
}