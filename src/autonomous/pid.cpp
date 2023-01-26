//PID (Proportional Integral Derivative) motion controller

#include "autonomous\pid.h"

PID::PID(float (*process)(), float target, float kP, float kI, float kD) 
  : measurement(process), proportionalCoefficient(kP), integralCoefficient(kI), derivativeCoefficient(kD) {}