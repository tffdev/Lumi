#include "toplevelmanager.h"
#include <QMessageBox>
#include <ui_mainwindow.h>
#include <QFileDialog>
#include <QProcess>
#include <filesystem.h>

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

void TopLevelManager::open_config_tab() {
  get_tab_widget()->open_config_tab(get_database()->get_config_node());
}

void TopLevelManager::open_asset_at_tree_item(QTreeWidgetItem *item, int) {
  if(item->parent() == nullptr) return;
  int item_id = get_tree_widget()->get_item_id_at_widget(item);
  AssetEntry* a = get_database()->get_asset(item_id);
  if(a == nullptr) throw "Asset Tree item fetch returned null.";
  get_tab_widget()->open_asset_in_tab(a);
}

/*
 * This runs the project in-place of the save directory, rather
 * than a temp folder.
 */
bool TopLevelManager::run_current_project() {

  // REQUEST PROJECT SAVE HERE
  // CURRENTLY ASSUMES THE GAME IS SAVED

  // Checks to see if the project is viable
  bool has_room = false;
  for(std::pair<int, AssetEntry*> kv : *get_database()->get_map()) {
    if(kv.second->type == ASSET_TYPE::ROOM) {
      has_room = true;
      break;
    }
  }
  if(!has_room) {
    show_error_message("Your game needs at least 1 room to run.");
    return false;
  }

  // - check for lumi engine executable
  show_statusbar_message("Attempting to run game...");
  if(!QFile::exists("./Core.exe")) {
    show_error_message("Core.exe is not in the editor's root directory.");
    return false;
  }

  // - execute inside temp directory
  show_statusbar_message("Running game!");
  QProcess::execute("./Core.exe", { get_database()->get_current_project_file_directory() });

  return true;
}
