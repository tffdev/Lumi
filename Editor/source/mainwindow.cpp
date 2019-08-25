#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <toplevelmanager.h>
#include <string>
#include <QFileDialog>
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


void MainWindow::open_load_project_dialog() {
  // Ask the user to load a .lumi file
  QString q_filename = QFileDialog::getOpenFileName(this, "Load Lumi Project", QString(), "Lumi File (*.lumi)");
  std::string filename(q_filename.toUtf8().data());

  // push filename to projectdata utility function
  toplevelmanager->get_database()->load_project_from_file_into_database(filename);
  toplevelmanager->get_tab_widget()->close_all_tabs();
  toplevelmanager->get_tree_widget()->load_database_into_tree(toplevelmanager->get_database());
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

void MainWindow::on_assetTree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
  int item_id = toplevelmanager->get_tree_widget()->get_item_id_at_widget(item);
  AssetEntry* a = toplevelmanager->get_database()->get_asset(item_id);

  if(a == nullptr) throw "Asset Tree item fetch returned null.";

  toplevelmanager->get_tab_widget()->open_asset_in_tab(a);
}
