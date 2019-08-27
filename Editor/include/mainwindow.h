#pragma once
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <asset_types.h>
#include <ui_mainwindow.h>
#include <toplevelmanager.h>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_loadButton_clicked();
  void on_actionLoad_triggered();
  void on_openGameSettings_clicked();
  void on_assetTree_itemDoubleClicked(QTreeWidgetItem *item, int);
  void on_saveButton_clicked();
  void on_actionOpenProjectSettings_triggered();
  void on_actionSave_triggered();
  void on_actionSave_Project_As_triggered();
  void on_actionReload_Stylesheet_triggered();
  void on_runButton_clicked();

private:
  void open_load_project_dialog();
  void request_project_save();
  bool project_save_as();
  void style_main_window();
  void reload_window_title();

  Ui::MainWindow *ui;
  TopLevelManager* toplevelmanager;
};
