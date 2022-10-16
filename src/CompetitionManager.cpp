#include "CompetitionManager.h"
#include "vex.h"

#include <iostream>

CompetitionManager::CompetitionManager(void (*driver)(), void (*auton)()) {
  this->comp.drivercontrol(driver);
  this->comp.autonomous(auton);
}

competition CompetitionManager::getCurrentCompetition() { return this->comp; }