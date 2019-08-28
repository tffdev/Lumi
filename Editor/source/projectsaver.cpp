#include "include/projectsaver.h"
#include <QDir>
#include <QFileDialog>
#include <filesystem.h>

bool ProjectSaver::request(TopLevelManager* toplevelmanager) {
  QDir qdir;

  if(qdir.exists(toplevelmanager->get_database()->get_current_project_file_directory())) {
    // Save directly to current project
    QString directory_url = toplevelmanager->get_database()->get_current_project_file_directory();
    QString dir_name = toplevelmanager->get_database()->get_current_project_file_name();
    if(FileSystem::write_to_file(toplevelmanager->get_database()->get_project_xml_as_string().c_str(), directory_url + "/" + dir_name)) {
      toplevelmanager->show_statusbar_message("Project saved successfully");
      return true;
    } else {
      toplevelmanager->show_statusbar_message("Project could not be saved due to an internal error.");
      return false;
    }
  } else {
    return ProjectSaver::save_as(toplevelmanager);
  }
}


bool ProjectSaver::save_as(TopLevelManager* toplevelmanager) {
  // Open dialog asking WHERE to save to
  QString directory_url = QFileDialog::getSaveFileName(
        nullptr, "Choose where to save your Lumi Project", "my_lumi_project", "", nullptr, QFileDialog::ShowDirsOnly);

  if(directory_url.compare("") == 0) {
    toplevelmanager->show_statusbar_message("Project save cancelled.");
    return false;
  }

  // Should this check be in place? If it's not,
  // it allows users to overwrite existing files. (They are prompted!)
  if(QFile::exists(directory_url)) {
    toplevelmanager->show_error_message("Specified file/directory already exists.");
    return false;
  }

  QString dir_name = directory_url.split('/').last();

  // This shouldn't ever happen unless something goes wrong on our end
  if(dir_name.compare("") == 0) {
    toplevelmanager->show_error_message("No filename given: Project has not been saved.");
    return false;
  }

  // How to defer project name?
  printf("saving project %s to %s\n", dir_name.toUtf8().data(), directory_url.toUtf8().data());

  // Make the directory
  QDir dir;
  dir.mkdir(directory_url);

  if(FileSystem::write_to_file(toplevelmanager->get_database()->get_project_xml_as_string().c_str(), directory_url + "/" + dir_name + ".lumi")) {
    toplevelmanager->show_statusbar_message("Project saved successfully");
    return true;
  } else {
    toplevelmanager->show_statusbar_message("Project could not be saved due to an internal error.");
    return false;
  }
}
