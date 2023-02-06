//Header for odometry.cpp

#pragma once
#include "vex.h"

int updateRobotPosition();

void startOdometry(float yPosition, float xPosition, float angle);

void updateDistance();

float getDistanceToGoal();

float getAngleToGoal();