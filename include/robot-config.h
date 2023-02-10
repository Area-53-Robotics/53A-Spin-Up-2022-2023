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
extern motor Roller;
extern digital_out Expander;
extern inertial InertialSensor;
extern digital_out FlywheelRamp;
extern rotation TrackParallel;
extern rotation TrackPerpendicular;
extern motor Indexer;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );