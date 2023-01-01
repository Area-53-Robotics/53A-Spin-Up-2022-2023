//Header for flywheel.cpp

#pragma once
#include "vex.h"

int printFlywheelSpeed();

void setFlywheelSpeed(float speed, velocityUnits units = velocityUnits::pct);

void changeFlywheelSpeed(float speedDifference);

void stopFlywheel();

void closestFlywheel();

void rollerFlywheel();