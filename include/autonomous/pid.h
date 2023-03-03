//Header for pid.cpp

#pragma once
#include "vex.h"

class PID {
  private:
  float (*measurement)();
  float setPoint;
  const float proportionalCoefficient;
  const float integralCoefficient;
  const float derivativeCoefficient;
  float currentError;
  float totalError;
  float previousError;
  float errorChange;
  mutex guard;

  public:
  PID(float (*process)(), float target, float kP, float kI = 0, float kD = 0);

  float update();

  void set(float target);
};