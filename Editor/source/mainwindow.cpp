#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <toplevelmanager.h>
#include <string>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  toplevelmanager = new TopLevelManager(ui);
  ui->assetTree->set_tlm(toplevelmanager);
  ui->editorTabs->set_tlm(toplevelmanager);

  style_main_window();
}

MainWindow::~MainWindow() {
  delete ui;
  delete toplevelmanager;
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

  // push filename to projectdata utility function
  toplevelmanager->get_database()->load_project_file_into_database(q_filename);
  toplevelmanager->get_tab_widget()->close_all_tabs();
  toplevelmanager->get_tree_widget()->load_database_into_tree(toplevelmanager->get_database());

  reload_window_title();
}

void MainWindow::request_project_save() {
  QDir qdir;

  if(qdir.exists(toplevelmanager->get_database()->get_current_project_file_directory())) {
    // Save directly to current project
    QString directory_url = toplevelmanager->get_database()->get_current_project_file_directory();
    QString dir_name = toplevelmanager->get_database()->get_current_project_file_name();
    if(toplevelmanager->get_database()->save_current_project_to_file(directory_url, dir_name)) {
      toplevelmanager->show_statusbar_message("Project saved successfully");
    } else {
      toplevelmanager->show_statusbar_message("Project could not be saved due to an internal error.");
    }
  } else {
    project_save_as();
  }
  reload_window_title();
}

bool MainWindow::project_save_as() {
  // Open dialog asking WHERE to save to
  QString directory_url = QFileDialog::getSaveFileName(this, "Choose where to save your Lumi Project", "my_lumi_project", "",
                                                       nullptr, QFileDialog::ShowDirsOnly);

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

  if(toplevelmanager->get_database()->save_current_project_to_file(directory_url, dir_name)) {
    toplevelmanager->show_statusbar_message("Project saved successfully");
    return true;
  } else {
    toplevelmanager->show_statusbar_message("Project could not be saved due to an internal error.");
    return false;
  }
}


/*****************************************
 * SLOTS
 *****************************************/
void MainWindow::on_loadButton_clicked() {
  open_load_project_dialog();
}

void MainWindow::on_actionLoad_triggered() {
  open_load_project_dialog();
}

void MainWindow::on_openGameSettings_clicked() {
  ui->editorTabs->open_config_tab(toplevelmanager->get_database()->get_config_node());
}

void MainWindow::on_assetTree_itemDoubleClicked(QTreeWidgetItem *item, int) {
  if(item->parent() == nullptr) return;

  int item_id = toplevelmanager->get_tree_widget()->get_item_id_at_widget(item);
  AssetEntry* a = toplevelmanager->get_database()->get_asset(item_id);

  if(a == nullptr) throw "Asset Tree item fetch returned null.";

  toplevelmanager->get_tab_widget()->open_asset_in_tab(a);
}

void MainWindow::on_saveButton_clicked() {
    request_project_save();
}
