//Header for flywheel.cpp

#pragma once
#include "vex.h"

int printFlywheelSpeed();

void setFlywheelSpeed(float speed, velocityUnits units = velocityUnits::pct);

void changeFlywheelSpeed(float speedDifference);

void incrementFlywheel();

void decrementFlywheel();

void stopFlywheel();

void closestFlywheel();

void rollerFlywheel();

void lowGoalFlywheel();

void maxFlywheel();