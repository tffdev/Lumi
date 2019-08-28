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
  ProjectRunner(QString lumi_filename, QString directory);
  int execute();
private:
  QString lumi_filename;
  QString directory;
};

