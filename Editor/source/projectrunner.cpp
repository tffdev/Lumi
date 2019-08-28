#include "include/projectrunner.h"
#include <QProcess>
#include <QFile>
#include <external/pugixml.hpp>

ProjectRunner::ProjectRunner(QString lumi_filename, QString directory)
  : lumi_filename(lumi_filename), directory(directory) {}

int ProjectRunner::execute() {
  // REQUEST PROJECT SAVE HERE
  // CURRENTLY ASSUMES THE GAME IS SAVED

  // Checks to see if the project is viable
  pugi::xml_document document;
  document.load_file((directory + "/" + lumi_filename).toUtf8().data());

  bool has_room = false;
  // Assuming that a project's "rooms" field containing children means the project has at least 1 room.
  for(pugi::xml_node node : document.child("project").child("rooms").children("room")) {
    if(node.empty() == false) has_room = true;
  }

  if(!has_room)
    return PROJECT_RUNNER_STATUS::NO_ROOMS;

  // - check for lumi engine executable
  if(!QFile::exists("./Core.exe"))
    return PROJECT_RUNNER_STATUS::NO_CORE;

  if(QProcess::execute("./Core.exe", { directory }) != 0)
    return PROJECT_RUNNER_STATUS::OTHER;

  return PROJECT_RUNNER_STATUS::OK;
}
