#pragma once
#include <QMainWindow>
#include <QTreeWidgetItem>
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
  void on_actionLoad_triggered();
  void on_assetTree_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
  void load_project();
  void style_main_window();

  Ui::MainWindow *ui;
  Configuration config;
  QString last_open_filename;
};
