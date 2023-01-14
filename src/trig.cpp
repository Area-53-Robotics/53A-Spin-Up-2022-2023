//Trig-related math functions, mostly for encoder-based turning

#include "trig.h"

float toDegrees(float radians) {
  return (radians * 180) / M_PI;
}

float toRadians(float degrees) {
  return (degrees * M_PI) / 180;
}

float arcLength(float arcMeasure, float radius) {
  return toRadians(arcMeasure) * radius;
}

float arcMeasure(float arcLength, float radius) {
  return toDegrees(arcLength / radius);
}