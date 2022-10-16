#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain Brain;

controller joystick = controller();

motor frontRightDrive = motor(PORT10, ratio18_1, true);
motor backRightDrive = motor(PORT11, ratio18_1, true);
motor frontLeftDrive = motor(PORT17, ratio18_1, false);
motor backLeftDrive = motor(PORT18, ratio18_1, false);
motor intake = motor(PORT12, ratio36_1, true);
motor flywheel = motor(PORT19, ratio18_1, true);
digital_out extension = digital_out(Brain.ThreeWirePort.A);
digital_out pusher = digital_out(Brain.ThreeWirePort.B);

void vexcodeInit(void) {}