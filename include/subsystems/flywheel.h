//Header for flywheel.cpp

#pragma once
#include "vex.h"

extern mutex controllerScreen;

int printFlywheelInfo();

void setFlywheelSpeed(float speed, velocityUnits units = rpm);

void changeFlywheelSpeed(float speedDifference);

void incrementFlywheel();

void decrementFlywheel();

void stopFlywheel();

void closestFlywheel();

void rollerFlywheel();

void lowGoalFlywheel();

void maxFlywheel();

void toggleFlywheelRamp();