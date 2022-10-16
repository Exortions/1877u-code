#include "actions.h"
#include "vex.h"

bool isFlywheeling = false;
bool isIntaking = false;
bool isPushing = false;

void toggleFlywheel() {
  isFlywheeling = !isFlywheeling;

  flywheel.setVelocity(isFlywheeling ? 100 : 0, percent);
  flywheel.spin(forward);
}

void reverseIntake() {
  isIntaking = true;

  intake.setVelocity(100, percent);
  intake.spin(reverse);
}

void toggleIntake() {
  isIntaking = !isIntaking;

  intake.setVelocity(isIntaking ? 100 : 0, percent);
  intake.spin(forward);
}

void retract() {
  isPushing = false;

  pusher.set(isPushing);
}

void push() {
  isPushing = !isPushing;

  pusher.set(isPushing);
}

bool getFlywheel() { return isFlywheeling; }

bool getPushing() { return isPushing; }

bool getIntake() { return isIntaking; }

void setFlywheel(bool newFlywheel) {
  isFlywheeling = newFlywheel;

  flywheel.setVelocity(isFlywheeling ? 100 : 0, percent);
  flywheel.spin(forward);
}

void setIntake(bool newIntake) {
  isIntaking = false;

  flywheel.setVelocity(isFlywheeling ? 100 : 0, percent);
  flywheel.spin(forward);
}