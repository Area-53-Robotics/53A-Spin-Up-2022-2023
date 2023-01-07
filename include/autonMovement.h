//Header for autonMovement.cpp

#pragma once
#include "vex.h"

void move(float length, float speed, bool blocking = true);

void rotateOneSideEncoder(float angle, turnType direction, float initialSpeed);

void rotateBothSidesEncoder(float angle, turnType direction, float initialSpeed);

void rotateOneSideInertial(float angle, turnType direction, float initialSpeed);

void rotateBothSidesInertial(float angle, turnType direction, float initialSpeed);

void rotateOneSide(float angle, turnType direction, float initialSpeed = 20, float sensor = true);

void rotateBothSides(float angle, turnType direction, float initialSpeed = 20, float sensor = true);