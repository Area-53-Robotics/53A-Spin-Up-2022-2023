//Track the position of the robot using the inertial sensor and the rotation of tracking wheels

#include "odometry.h"

/*(0,0) is corner closest to the driver station (not the one with the net)
X is along the side the drivers stand on
Y is along the other side
"goal" refers to the goal you need to shoot into, not the goal on your side*/

const float goalXPosition = 17.78;
const float goalYPosition = 122.63;
const float trackingWheelRadius = 2.75/2;
float robotXPosition;
float robotYPosition;

int updateRobotPosition() {
  float parallelAngle = 0;
  float perpendicularAngle = 0;
  float previousParallelAngle = 0;
  float previousPerpendicularAngle = 0;
  float parallelAngleChange;
  float perpendicularAngleChange;
  float parallelDistance;
  float perpendicularDistance;
  TrackParallel.resetPosition();
  TrackPerpendicular.resetPosition();

  while (1) {
    parallelAngle = TrackParallel.position(degrees);
    perpendicularAngle = TrackPerpendicular.position(degrees);
    parallelAngleChange = parallelAngle - previousParallelAngle;
    perpendicularAngleChange = perpendicularAngle - previousPerpendicularAngle;

    parallelDistance = arcLength(parallelAngleChange, trackingWheelRadius);
    perpendicularDistance = arcLength(perpendicularAngleChange, trackingWheelRadius);
  }

  return 1;
}

float getDistanceToGoal() {
  float xDifference = robotXPosition - goalXPosition;
  float yDifference = robotYPosition - goalYPosition;
  return sqrt(pow(xDifference, 2) + pow(yDifference, 2));
}

float getAngleToGoal() {
  return 0;
}