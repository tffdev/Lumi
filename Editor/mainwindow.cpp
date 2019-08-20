#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Lumi Game Creator");
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_editorTabs_tabCloseRequested(int index) {
  ui->editorTabs->removeTab(index);
}

template <typename T>
void MainWindow::insert_widgets(int itemnum, Database<T>* db) {
  QTreeWidgetItem* toplvlitem = ui->assetTree->topLevelItem(itemnum);
  foreach(QTreeWidgetItem* i, toplvlitem->takeChildren()) delete i;
  for(auto asset : db->get_all_assets()) {
    QTreeWidgetItem* child = new QTreeWidgetItem(toplvlitem, { asset.name.c_str() });
    child->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    child->sortChildren(0, Qt::SortOrder::AscendingOrder);
    toplvlitem->insertChild(-1, child);
  }
}

void MainWindow::load_database_into_tree() {
  insert_widgets(0, &database.objects);
  insert_widgets(1, &database.sprites);
  insert_widgets(2, &database.backgrounds);
  insert_widgets(3, &database.sounds);
  insert_widgets(4, &database.tilesets);
  insert_widgets(5, &database.rooms);

  // sort items
  for(int i=0; i < ui->assetTree->topLevelItemCount(); i++){
    ui->assetTree->topLevelItem(i)->sortChildren(0, Qt::SortOrder::AscendingOrder);
  }
}

void MainWindow::load_project() {
  // Ask the user to load a .lumi file
  QString qfilename = QFileDialog::getOpenFileName(this, "Load Lumi Project", QString(), "Lumi File (*.lumi)");
  std::string filename(qfilename.toUtf8().data());

  // does nothing if user escapes the file dialog
  if(filename.compare("") == 0) return;

  /* If the .lumi file is invalid,
   * throw a message box displaying the error. */
  if(!database.load_project_file_into_db(filename)) {
    QMessageBox mb;
    mb.setWindowTitle("Error Loading Project");
    mb.setText("Error parsing project file " + qfilename.split("/").last());
    mb.setIcon(QMessageBox::Critical);
    mb.exec();
  } else {
    ui->statusBar->showMessage("Loaded project successfully!");
    load_database_into_tree();
  }
}

void MainWindow::on_loadButton_clicked() {
    load_project();
}
void MainWindow::on_actionLoad_triggered() {
  load_project();
}
