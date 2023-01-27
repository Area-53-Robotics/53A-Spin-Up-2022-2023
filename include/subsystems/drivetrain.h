//Header for drivetrain.cpp

#pragma once
#include "vex.h"
#include <cmath>

float driveCurve(float joystickPosition);

void updateDriveSpeed();

void stopDrive();

void setDriveStopping(brakeType stopType);

void setDriveTimeout(float time);

float getRotation();