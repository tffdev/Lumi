#pragma once
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <ui_mainwindow.h>
#include <asset_types.h>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  Ui::MainWindow* get_ui();

private slots:
  void on_loadButton_clicked();
  void on_actionLoad_triggered();

private:
  void load_project();
  void style_main_window();

  Ui::MainWindow *ui;
  Configuration config;
  QString last_open_filename;
};


#define GET_MAIN_WINDOW() qobject_cast<MainWindow*>(QApplication::topLevelWidgets().at(0))
