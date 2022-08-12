using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FlywheelFront;
extern controller Controller1;
extern motor LeftFront;
extern motor LeftTop;
extern motor LeftBack;
extern motor RightBack;
extern motor RightTop;
extern motor RightFront;
extern motor Intake;
extern motor FlywheelBack;
extern digital_out Indexer;
extern digital_out Expander;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );