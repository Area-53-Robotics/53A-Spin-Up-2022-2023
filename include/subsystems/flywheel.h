//Header for flywheel.cpp

#pragma once
#include "vex.h"

extern mutex controllerScreen;

int printFlywheelInfo();

int updateFlywheelSpeed();

float getFlywheelSpeed();

void setFlywheelSpeed(float speed, velocityUnits units = rpm);

void changeFlywheelSpeed(float speedDifference, velocityUnits units = rpm);

void stopFlywheel();