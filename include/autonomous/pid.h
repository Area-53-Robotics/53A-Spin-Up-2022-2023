//Header for pid.cpp

#pragma once
#include "vex.h"

void startPID(float (*measurement)(), float setPoint, float proportionalCoefficient, float integralCoefficient = 0, float derivativeCoefficient = 0);