//Header for intake.cpp

#pragma once
#include "vex.h"

void spinIntake(directionType direction);

void stopIntake();

void setIntakeForward();

void setIntakeReverse();

void updateIntake();

void rotateRoller(float angle, bool blocking = true);

void setIntakeTimeout(float time);