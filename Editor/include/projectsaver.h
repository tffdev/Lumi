#pragma once
#include <toplevelmanager.h>

class ProjectSaver
{
public:
  ProjectSaver();
  static bool request(TopLevelManager* toplevelmanager);
  static bool save_as(TopLevelManager* toplevelmanager);
};

