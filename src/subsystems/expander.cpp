//Functions for controlling pistons on expanders

#include "subsystems\expander.h"

void expand() {
  Expander.set(true);
}

void checkExpansion() {
  if (Controller1.ButtonB.pressing() && Controller1.ButtonDown.pressing()) {
    expand();
  }
}