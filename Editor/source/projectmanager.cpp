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
