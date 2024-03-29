#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Flywheel = motor(PORT1, ratio6_1, false);
controller Controller1 = controller(primary);
motor LeftFront = motor(PORT9, ratio18_1, true);
motor LeftBack = motor(PORT10, ratio18_1, true);
motor RightBack = motor(PORT8, ratio18_1, false);
motor RightFront = motor(PORT7, ratio18_1, false);
motor Intake = motor(PORT11, ratio6_1, true);
motor Roller = motor(PORT15, ratio36_1, true);
digital_out Expander = digital_out(Brain.ThreeWirePort.B);
inertial InertialSensor = inertial(PORT6);
digital_out FlywheelRamp = digital_out(Brain.ThreeWirePort.C);
rotation TrackParallel = rotation(PORT19, false);
rotation TrackPerpendicular = rotation(PORT20, false);
motor Indexer = motor(PORT2, ratio18_1, true);
rotation FlywheelSensor = rotation(PORT3, false);

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