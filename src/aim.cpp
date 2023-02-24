//Aim the flywheel using odometry

#include "aim.h"

float shotArcRadius;
const float contactRadius = 4; //inches from flywheel axle to contact point of flywheel and disk

float getDiskVelocity() { //inches per second
  float motorRPM = Flywheel.velocity(velocityUnits::rpm);
  float wheelRPM = motorRPM * 6;
  float diskVelocity = (M_PI * contactRadius * wheelRPM) / 30;
  return diskVelocity;
}