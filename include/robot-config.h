using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Flywheel;
extern controller Controller1;
extern motor LeftFront;
extern motor LeftBack;
extern motor RightBack;
extern motor RightFront;
extern motor Intake;
extern motor RightTop;
extern digital_out Indexer;
extern digital_out Expander;
extern motor LeftTop;
extern rotation FlywheelSensor;
extern inertial InertialSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );