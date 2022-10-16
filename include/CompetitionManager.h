#include "vex.h"

class CompetitionManager {
public:
  CompetitionManager(void (*driver)(), void (*auton)());
  competition getCurrentCompetition();

private:
  competition comp;
};