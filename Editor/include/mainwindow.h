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
  Ui::MainWindow* get_ui();

private slots:
  void on_loadButton_clicked();
  void on_actionLoad_triggered();

  void on_openGameSettings_clicked();

  void on_assetTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
  void open_load_project_dialog();
  void style_main_window();

  Ui::MainWindow *ui;
  QString last_open_filename;

  TopLevelManager* toplevelmanager;
};


#define GET_MAIN_WINDOW() qobject_cast<MainWindow*>(QApplication::topLevelWidgets().at(0))
