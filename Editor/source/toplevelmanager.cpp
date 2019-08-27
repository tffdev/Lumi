#include "toplevelmanager.h"
#include <QMessageBox>
#include <ui_mainwindow.h>
#include <QFileDialog>
#include <QProcess>

TopLevelManager::TopLevelManager(Ui::MainWindow* ui_pointer) : ui(ui_pointer) {
  database = new ProjectData;
  editor_tabs_widget = ui->editorTabs;
  asset_tree_widget = ui->assetTree;
}

TopLevelManager::~TopLevelManager() {
  delete database;
}

EditorTabs* TopLevelManager::get_tab_widget() {
  return editor_tabs_widget;
}
AssetTree* TopLevelManager::get_tree_widget() {
  return asset_tree_widget;
}

void TopLevelManager::show_error_message(QString text) {
  QMessageBox mb;
  mb.setWindowTitle("Error");
  mb.setText(text);
  mb.setIcon(QMessageBox::Critical);
  mb.exec();
}

void TopLevelManager::show_statusbar_message(QString text) {
  ui->statusBar->showMessage(text, 5000);
}

ProjectData* TopLevelManager::get_database() {
  return database;
}

void TopLevelManager::set_modified_since_last_save(bool set_to) {
  modified_since_last_save = set_to;
}

bool TopLevelManager::has_been_modified_since_last_save() {
  return modified_since_last_save;
}

bool TopLevelManager::run_current_project() {
  // Show a "load" dialog for compilation of the game


  // - check for lumi engine executable
  show_statusbar_message("Attempting to run game...");
  if(!QFile::exists("./Core.exe")) {
    show_error_message("Core.exe is not in the editor's root directory.");
    return false;
  }

  // - build executable into temp directory / engine
  QDir dir =  QDir::temp();
  dir.mkdir("lumi_game");
  dir.cd("lumi_game");
  dir.mkdir("engine");
  if(QFile::exists(dir.path() + "/engine/Core.exe")) QFile::remove(dir.path() + "/engine/Core.exe");

  QFile::copy("./Core.exe", dir.path() + "/engine/Core.exe");
  printf("%s\n", dir.path().toUtf8().data());

  // - copy game data into temp directory / data


  // - execute
  show_statusbar_message("Running game!");
  QProcess::execute(dir.path() + "/engine/Core.exe");

  // - clear temp dir
}
