#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Flywheel = motor(PORT1, ratio6_1, false);
controller Controller1 = controller(primary);
motor LeftFront = motor(PORT11, ratio18_1, true);
motor LeftBack = motor(PORT13, ratio18_1, true);
motor RightBack = motor(PORT14, ratio18_1, false);
motor RightFront = motor(PORT16, ratio18_1, false);
motor Intake = motor(PORT10, ratio6_1, true);
motor RightTop = motor(PORT15, ratio6_1, true);
digital_out Indexer = digital_out(Brain.ThreeWirePort.A);
digital_out Expander = digital_out(Brain.ThreeWirePort.B);
motor LeftTop = motor(PORT12, ratio6_1, false);
rotation FlywheelSensor = rotation(PORT2, false);
inertial InertialSensor = inertial(PORT20);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}