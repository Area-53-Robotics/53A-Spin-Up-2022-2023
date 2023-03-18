//Functions and values related to shooting

#include "subsystems\firing.h"

mutex indexerLock;
//int startingPosition = 160;
float delay = 0.11;
bool shooting = false;

void startIndexer() {
  //Indexer.rotateFor(forward, startingPosition, degrees, 100, velocityUnits::pct, false);
}

void toggleIndexer() {
  shooting = !shooting;
}

void updateIndexer() {
  indexerLock.lock();
  if (shooting) {
    Indexer.spin(forward, 100, pct);
  } else if (Controller1.ButtonR1.pressing()) {
    Indexer.spin(reverse, 100, pct);
  } else {
    Indexer.stop();
  }
  indexerLock.unlock();
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
  indexerLock.lock();
  if (!CompressionBar.value()) {
    CompressionBar.set(true);
    wait(0.03, sec);
  }
  Indexer.rotateFor(forward, 720, degrees, 100, velocityUnits::pct);
  CompressionBar.set(false);
  indexerLock.unlock();
}

void toggleCompression() {
  CompressionBar.set(!CompressionBar.value());
}

void releaseIndexer() {
  Indexer.stop(coast);
}