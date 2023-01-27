//PID (Proportional Integral Derivative) motion controller

#include "autonomous\pid.h"

PID::PID(float (*process)(), float target, float kP, float kI, float kD) 
  : measurement(process), proportionalCoefficient(kP), integralCoefficient(kI), derivativeCoefficient(kD) {
    currentError = 0;
    totalError = 0;
    previousError = 0;
    errorChange = 0;
  }

float PID::update() {
  currentError = setPoint - measurement();
  totalError += currentError;
  errorChange = currentError - previousError;
  previousError = currentError;

  return currentError * proportionalCoefficient + totalError * integralCoefficient + errorChange * derivativeCoefficient;
}