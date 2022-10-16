#include "pre-auton.h"
#include "actions.h"
#include "vex.h"

#include <iostream>

void pre_auton() {
  std::cout << "Performing pre autonomous tasks...";

  flywheel.setVelocity(0, percent);
  flywheel.stop();

  intake.setVelocity(0, percent);
  intake.stop();

  pusher.set(false);
}