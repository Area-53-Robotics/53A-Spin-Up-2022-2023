using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FlywheelHigher;
extern controller Controller1;
extern motor LeftFront;
extern motor LeftBack;
extern motor RightBack;
extern motor RightFront;
extern motor IntakeHigher;
extern motor FlywheelLower;
extern digital_out Indexer;
extern digital_out Expander;
extern motor IntakeLower;
extern rotation FlywheelSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );