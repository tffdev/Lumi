#include "toplevelmanager.h"
#include <QMessageBox>
#include <ui_mainwindow.h>
#include <QFileDialog>

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
