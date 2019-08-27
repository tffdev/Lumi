#pragma once
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <ui_mainwindow.h>
#include <asset_types.h>
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

private:
  void open_load_project_dialog();
  void request_project_save();
  bool project_save_as();

  void style_main_window();

  void reload_window_title();

  Ui::MainWindow *ui;
  TopLevelManager* toplevelmanager;
};
