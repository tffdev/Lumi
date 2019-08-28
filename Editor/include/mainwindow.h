#pragma once
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <asset_types.h>
#include <toplevelmanager.h>
#include <ui_mainwindow.h>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  // Main window meta
  void style_main_window();
  void reload_window_title();

  // Loading/saving
  void open_load_project_dialog();
  void request_project_save();
  void request_project_save_as();

  Ui::MainWindow *ui;
  TopLevelManager* toplevelmanager;
};
