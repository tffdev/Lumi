#include "maindatamanager.h"

Ui::MainWindow* MainDataManager::get_ui() {
  if(ui == nullptr) throw "MainDataManager UI item fetch request before it was passed.";
  return ui;
}

void MainDataManager::pass_ui(Ui::MainWindow *input_ui) {
  ui = input_ui;
}
