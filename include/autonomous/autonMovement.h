//Header for autonMovement.cpp

#pragma once
#include "vex.h"

void move(float length, float speed, bool blocking = true);

void rotateOneSideEncoder(float angle, turnType direction, float initialSpeed);

void rotateBothSidesEncoder(float angle, turnType direction, float initialSpeed, float margin = 1);

void rotateOneSideInertial(float angle, turnType direction, float initialSpeed);

void rotateBothSidesInertial(float angle, turnType direction, float initialSpeed, float margin = 1);

void rotateOneSide(float angle, turnType direction, float initialSpeed = 20, bool sensor = true);

void rotateBothSides(float angle, turnType direction, float initialSpeed = 20, bool sensor = true, float margin = 1);