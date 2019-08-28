#pragma once
#include <toplevelmanager.h>

enum PROJECT_RUNNER_STATUS {
  OK,
  NO_ROOMS,
  NO_CORE,
  OTHER
};

class ProjectRunner
{
public:
  ProjectRunner(TopLevelManager* tlm, QString directory);
  int execute();
private:
  TopLevelManager* tlm;
  QString directory;
};

