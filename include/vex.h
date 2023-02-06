/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"
#include "trig.h"
#include "subsystems\flywheel.h"
#include "subsystems\intake.h"
#include "subsystems\expander.h"
#include "subsystems\drivetrain.h"
#include "subsystems\indexer.h"
#include "autonomous\autonMovement.h"
#include "autonomous\autonSelector.h"
#include "autonomous\autonPrograms.h"
#include "autonomous\pid.h"
#include "autonomous\recording.h"
#include "brainScreen.h"
#include "odometry.h"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)