#include "include/projectrunner.h"
#include <QProcess>
#include <QFile>

ProjectRunner::ProjectRunner(TopLevelManager* tlm, QString directory)
  : tlm(tlm), directory(directory) {}

int ProjectRunner::execute() {
  // REQUEST PROJECT SAVE HERE
  // CURRENTLY ASSUMES THE GAME IS SAVED

  // Checks to see if the project is viable
  bool has_room = false;
  for(std::pair<int, AssetEntry*> kv : *tlm->get_database()->get_map()) {
    if(kv.second->type == ASSET_TYPE::ROOM) {
      has_room = true;
      break;
    }
  }

  if(!has_room) {
    return PROJECT_RUNNER_STATUS::NO_ROOMS;
  }

  // - check for lumi engine executable
  if(!QFile::exists("./Core.exe")) {
    return PROJECT_RUNNER_STATUS::NO_CORE;
  }

  if(QProcess::execute("./Core.exe", { directory }) != 0)
    return PROJECT_RUNNER_STATUS::OTHER;

  return PROJECT_RUNNER_STATUS::OK;
}
