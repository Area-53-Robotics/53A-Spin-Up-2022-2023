//Timers to notify driver of time left in match

#include "timers.h"
int notificationInstance = 0;
bool matchOver = false;
mutex controllerRumble;


void setTimers() { //Notify driver at 1 minute, 30 seconds, and 10 seconds left in match
  Brain.Timer.event(notify, 45000);
  Brain.Timer.event(notify, 75000);
  Brain.Timer.event(notify, 95000);
  Brain.Timer.event(stopRumble, 105000);
}

void notify() {
  notificationInstance++;
  switch (notificationInstance) {
    case 1:
    Controller1.rumble("-");
    break;

    case 2:
    Controller1.rumble("--");
    break;

    case 3:
    task notification(continuousControllerRumble);
    break;
  }
}

int continuousControllerRumble() {
  while (!Expander.value()) {
    Controller1.rumble("-");
    controllerRumble.lock();
    if (matchOver) {
      break;
    }
    controllerRumble.unlock();  
    task::sleep(100);
  }
  return 0;
}

void stopRumble() {
  controllerRumble.lock();
  matchOver = true;
  controllerRumble.unlock();
}