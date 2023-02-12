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
float yDifference;
float xDifference;
mutex positionLock;

int updateRobotPosition() {
  float parallelAngle = 0;
  float perpendicularAngle = 0;
  float previousParallelAngle = 0;
  float previousPerpendicularAngle = 0;
  float parallelAngleChange;
  float perpendicularAngleChange;
  float parallelDistance;
  float perpendicularDistance;
  float yDistance;
  float xDistance;
  float heading;
  TrackParallel.resetPosition();
  TrackPerpendicular.resetPosition();

  while (1) {
    positionLock.lock();
    parallelAngle = TrackParallel.position(degrees);
    perpendicularAngle = TrackPerpendicular.position(degrees);
    heading = toRadians(InertialSensor.heading(degrees));

    parallelAngleChange = parallelAngle - previousParallelAngle;
    perpendicularAngleChange = perpendicularAngle - previousPerpendicularAngle;

    parallelDistance = arcLength(parallelAngleChange, trackingWheelRadius);
    perpendicularDistance = arcLength(perpendicularAngleChange, trackingWheelRadius);

    yDistance = parallelDistance * cos(heading) + perpendicularDistance * sin(heading);
    xDistance = parallelDistance * sin(heading) + perpendicularDistance * cos(heading);

    robotYPosition += yDistance;
    robotXPosition += xDistance;
    positionLock.unlock();
    task::sleep(20);
  }
  return 1;
}

void startOdometry(float yPosition , float xPosition, float angle) { //Facing +X is 0 degrees
  robotYPosition = yPosition;
  robotXPosition = xPosition;
  InertialSensor.setHeading(angle, degrees);
  task odometer(updateRobotPosition);
}

void updateDistance() {
  yDifference = goalYPosition - robotYPosition;
  xDifference = goalXPosition - robotXPosition;
}

float getDistanceToGoal() {
  positionLock.lock();
  updateDistance();
  return sqrt(pow(xDifference, 2) + pow(yDifference, 2));
  positionLock.unlock();
}

float getAngleToGoal() {
  positionLock.lock();
  updateDistance();
  float angle = toDegrees(atan(yDifference / xDifference)) - InertialSensor.heading();
  if (xDifference < 0) {
    angle += 180;
  }
  positionLock.unlock();
  return angle;
}

void printRelativePosition() {
  controllerScreen.lock();
  Controller1.Screen.setCursor(1, 0);
  Controller1.Screen.print("%4.1f in. to goal", getDistanceToGoal());
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print("%3.1f degrees to goal", getAngleToGoal());
  controllerScreen.unlock();
}