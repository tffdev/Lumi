#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <maindatamanager.h>
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  MainDataManager::fetch().pass_ui(ui);
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

void MainWindow::load_project() {
  // Ask the user to load a .lumi file
  QString qfilename = QFileDialog::getOpenFileName(this, "Load Lumi Project", QString(), "Lumi File (*.lumi)");
  std::string filename(qfilename.toUtf8().data());

  // does nothing if user escapes the file dialog
  if(filename.compare("") == 0) return;

  /* If the .lumi file is invalid,
   * throw a message box displaying the error. */
  if(!ProjectData::db().load_project_file_into_databases(filename)) {
    QMessageBox mb;
    mb.setWindowTitle("Error Loading Project");
    mb.setText("Error parsing project file " + qfilename.split("/").last());
    mb.setIcon(QMessageBox::Critical);
    mb.exec();
  } else {
    ui->statusBar->showMessage("Loaded project successfully!");
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

void MainWindow::on_assetTree_itemDoubleClicked(QTreeWidgetItem* item, int) {
  // if top level item
  if(!item->parent()) return;

  // if tab is already open
  for(int i = 0; i < ui->editorTabs->count(); ++i) {
    QString text = ui->editorTabs->tabText(i);
    if(item->text(0) == text) {
      ui->editorTabs->setCurrentIndex(i);
      return;
    }
  }
  // open new tab
  int index = ui->editorTabs->addTab(new QWidget(), item->text(0));
  ui->editorTabs->setCurrentIndex(index);
}

void MainWindow::on_editorTabs_tabCloseRequested(int index) {
  // If unsaved changes, show a dialog?
  ui->editorTabs->removeTab(index);
}
