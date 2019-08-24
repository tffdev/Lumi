#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <projectmanager.h>
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ProjectManager::fetch().pass_ui(ui);
  ui->setupUi(this);
  style_main_window();
}

MainWindow::~MainWindow() {
  delete ui;
}

Ui::MainWindow* MainWindow::get_ui() {
  return ui;
}

void MainWindow::style_main_window() {
  this->setWindowTitle("Lumi Game Creator");
  QFile file(":/rc/style.css");
  if(!file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(nullptr, "error", file.errorString());
  }
  setStyleSheet(QString(file.readAll()));
  file.close();
}

/*****************************************
 * PROJECT LOADING AND SAVING
 *****************************************/
void MainWindow::load_project() {
  // Ask the user to load a .lumi file
  QString qfilename = QFileDialog::getOpenFileName(this, "Load Lumi Project", QString(), "Lumi File (*.lumi)");
  std::string filename(qfilename.toUtf8().data());

  // does nothing if user escapes the file dialog
  if(filename.compare("") == 0) return;

  /* If the .lumi file is invalid,
   * throw a message box displaying the error. */
  if(!ProjectData::fetch().load_project_file_into_database(filename)) {
    ProjectManager::fetch().show_error_message("Error parsing project file " + qfilename.split("/").last());
  } else {
    ProjectManager::fetch().set_statusbar_message("Loaded project successfully!");

    // clear all open tabs, if any
    ui->editorTabs->close_all_tabs();

    // load into tree
    ui->assetTree->load_database_into_tree();
  }
}

/*****************************************
 * SLOTS
 *****************************************/
void MainWindow::on_loadButton_clicked() {
  load_project();
}

void MainWindow::on_actionLoad_triggered() {
  load_project();
}


void MainWindow::on_openGameSettings_clicked() {
  ui->editorTabs->open_config_tab();
}
