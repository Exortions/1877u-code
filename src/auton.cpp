#include "auton.h"
#include "vex.h"

#include <iostream>

void move(int distance, int velocity) {
  frontRightDrive.setVelocity(velocity, percent);
  frontLeftDrive.setVelocity(velocity, percent);
  backRightDrive.setVelocity(velocity, percent);
  backLeftDrive.setVelocity(velocity, percent);

  frontRightDrive.spinFor(distance, degrees, false);
  frontLeftDrive.spinFor(distance, degrees, false);
  backRightDrive.spinFor(distance, degrees, false);
  backLeftDrive.spinFor(
      distance, degrees,
      true); // make sure this completes before next action starts
}

void turn(int angle, int velocity) {
  frontRightDrive.setVelocity(velocity, percent);
  frontLeftDrive.setVelocity(velocity, percent);
  backRightDrive.setVelocity(velocity, percent);
  backLeftDrive.setVelocity(velocity, percent);

  frontRightDrive.spinFor(angle, degrees, false);
  frontLeftDrive.spinFor(-angle, degrees, false);
  backRightDrive.spinFor(angle, degrees, false);
  backLeftDrive.spinFor(
      -angle, degrees,
      true); // make sure this completes before next action starts
}

void auton() {
  std::cout << "Running auton" << std::endl;

  // TODO: implement auton

  move(100, 100);
  turn(90, 100);
}