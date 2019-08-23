#include "projectmanager.h"
#include <QMessageBox>
#include <configurationeditor.h>

Ui::MainWindow* ProjectManager::get_ui() {
  if(ui == nullptr) throw "MainDataManager UI item fetch request before it was passed.";
  return ui;
}

void ProjectManager::pass_ui(Ui::MainWindow *input_ui) {
  ui = input_ui;
}

void ProjectManager::show_error_message(QString text) {
  QMessageBox mb;
  mb.setWindowTitle("Error");
  mb.setText(text);
  mb.setIcon(QMessageBox::Critical);
  mb.exec();
}

void ProjectManager::open_asset_in_tab(AssetEntry* asset) {
    ui->editorTabs->open_asset_in_tab(asset);
}

void ProjectManager::open_project_configuration_tab() {
  // if tab is already open
//  for(int i = 0; i < ui->editorTabs->count(); ++i) {
//    QString text = ui->editorTabs->tabText(i);
//    if(asset->name.compare(text.toStdString()) == 0) {
//      ui->editorTabs->setCurrentIndex(i);
//      return;
//    }
//  }

  // open new tab
  int index = ui->editorTabs->addTab(new ConfigurationEditor(), "Configuration");
  ui->editorTabs->setCurrentIndex(index);
}
