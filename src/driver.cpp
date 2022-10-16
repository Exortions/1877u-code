#include "driver.h"
#include "actions.h"
#include "vex.h"


#include <iostream>

bool shouldDebounceFlywheel = false;

void driver() {
  std::cout << "Running driver" << std::endl;

  while (true) {
    if (joystick.ButtonL2.pressing()) reverseIntake();
    else if (joystick.ButtonL1.pressing()) setIntake(true);
    else setIntake(false);

    if (joystick.ButtonLeft.pressing()) extension.set(true);
    if (joystick.ButtonR2.pressing()) toggleFlywheel();
    if (joystick.ButtonR1.pressing()) push();

    int RightAxis = joystick.Axis2.value();
    int LeftAxis = joystick.Axis3.value();

    if (RightAxis > 0 || RightAxis < 0) {
      frontRightDrive.setVelocity(RightAxis, percent);
      backRightDrive.setVelocity(RightAxis, percent);

      frontRightDrive.spin(forward);
      backRightDrive.spin(forward);
    }

    if (LeftAxis > 0 || LeftAxis < 0) {
      frontLeftDrive.setVelocity(LeftAxis, percent);
      backLeftDrive.setVelocity(LeftAxis, percent);

      frontLeftDrive.spin(forward);
      backLeftDrive.spin(forward);
    }

    wait(10, msec);
  }
}