//Functions for controlling pistons on indexer and expander

#include "subsystems\pistons.h"

void shoot() {
  Indexer.set(true);
  wait(0.2,sec);
  Indexer.set(false);
}

void expand() {
  Expander.set(true);
}

void checkExpansion() {
  if (Controller1.ButtonA.pressing() && Controller1.ButtonLeft.pressing()) {
    expand();
  }
}