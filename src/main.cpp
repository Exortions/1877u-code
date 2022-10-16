#include "CompetitionManager.h"
#include "auton.h"
#include "driver.h"
#include "pre-auton.h"
#include "vex.h"

#include <chrono>
#include <iostream>

using namespace vex;

const auto p1 = std::chrono::system_clock::now();

int getTime() {
  return std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch())
      .count();
}

void displayTimeTaken(int start) {
  std::cout << " [" << (getTime() - start) << "ms]" << std::endl;
}

int main() {
  // initialize vex
  int time = getTime();
  std::cout << "Initializing VEX";
  vexcodeInit();
  displayTimeTaken(time);

  // initialize competition
  CompetitionManager *manager = new CompetitionManager(driver, auton);

  competition comp = manager->getCurrentCompetition();

  // start pre auton tasks
  time = getTime();
  pre_auton();
  displayTimeTaken(time);

  // keep-alive
  while (true) {
    wait(100, msec);
  }
}
