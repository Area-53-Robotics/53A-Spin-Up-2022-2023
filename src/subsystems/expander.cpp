//Functions for controlling pistons on expanders

#include "subsystems\expander.h"

void expand() {
  Expander.set(true);
}

void checkExpansion() {
  if (Controller1.ButtonL2.pressing() && Controller1.ButtonR2.pressing()) {
    expand();
  }
}