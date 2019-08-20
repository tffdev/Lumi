#pragma once
#include <QMainWindow>
#include <projectdata.h>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_editorTabs_tabCloseRequested(int index);
  void on_loadButton_clicked();
  void on_actionLoad_clicked();

private:
  template <typename T>
  void insert_widgets(int itemnum, Database<T>* db);
  void load_project();
  void load_database_into_tree();

  Ui::MainWindow *ui;
  Configuration config;
  ProjectData database;
  QString last_open_filename;
};
