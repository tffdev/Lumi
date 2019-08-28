#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <toplevelmanager.h>
#include <string>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <projectsaver.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  toplevelmanager = new TopLevelManager(ui);
  ui->assetTree->set_tlm(toplevelmanager);
  ui->editorTabs->set_tlm(toplevelmanager);

  style_main_window();

  // SLOT CONNECTIONS
  // Buttons
  connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::request_project_save);
  connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::open_load_project_dialog);
  connect(ui->runButton, &QPushButton::clicked, this->toplevelmanager, &TopLevelManager::run_current_project);
  connect(ui->openGameSettings, &QPushButton::clicked, this->toplevelmanager, &TopLevelManager::open_config_tab);

  // Actions
  connect(ui->actionSave, &QAction::triggered, this, &MainWindow::request_project_save);
  connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::open_load_project_dialog);
  connect(ui->actionSave_Project_As, &QAction::triggered, this, &MainWindow::request_project_save_as);
  connect(ui->actionReload_Stylesheet, &QAction::triggered, this, &MainWindow::style_main_window);
  connect(ui->actionOpenProjectSettings, &QAction::triggered, toplevelmanager, &TopLevelManager::open_config_tab);

  // Misc
  connect(ui->assetTree, &QTreeWidget::itemDoubleClicked, toplevelmanager, &TopLevelManager::open_asset_at_tree_item);
}

MainWindow::~MainWindow() {
  delete ui;
  delete toplevelmanager;
}

void MainWindow::style_main_window() {
  setStyleSheet("");
  this->setWindowTitle("Lumi Game Creator");

  /* Check for stylesheet in this order:
   * - root directory
   * - ../editor directory
   * - embedded default stylesheet in resources */
  QFile file(":/rc/style.css");

  if(!file.open(QIODevice::ReadOnly)) {
      QMessageBox::information(nullptr, "error", file.errorString());
  }
  setStyleSheet(QString(file.readAll()));
  file.close();
}

void MainWindow::reload_window_title() {
  QString title("Lumi Game Creator");

  QString loaded_filename = toplevelmanager->get_database()->get_current_project_file_name();
  if(loaded_filename.compare("") != 0) {
    title.append(" - (" + loaded_filename + ")");
  }
  this->setWindowTitle(title);
}


void MainWindow::open_load_project_dialog() {
  // Ask the user to load a .lumi file
  QString q_filename = QFileDialog::getOpenFileName(this, "Load Lumi Project", QString(), "Lumi File (*.lumi)");

  if(q_filename.compare("") == 0)
    return toplevelmanager->show_statusbar_message("Project load cancelled.");

  // push filename to projectdata utility function
  if(!toplevelmanager->get_database()->load_project_file_into_database(q_filename))
    toplevelmanager->show_error_message("Error loading project " + q_filename);

  toplevelmanager->get_tab_widget()->close_all_tabs();

  toplevelmanager->get_tree_widget()->load_database_into_tree(toplevelmanager->get_database());

  reload_window_title();
}

// Should these be moved into the top level manager?
void MainWindow::request_project_save() {
  ProjectSaver::request(toplevelmanager);
  reload_window_title();
}


void MainWindow::request_project_save_as() {
  ProjectSaver::save_as(toplevelmanager);
  reload_window_title();
}
