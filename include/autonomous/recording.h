//Header for recording.cpp

#pragma once
#include "vex.h"
#include <fstream>
#include <string>

const motor recordedMotors[4] = {LeftFront, LeftBack, RightFront, RightBack};

int record();

void toggleRecording();