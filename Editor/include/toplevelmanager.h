#pragma once
#include <QString>
#include <QTreeWidgetItem>
#include <external/pugixml.hpp>
#include <projectdata.h>

// Circular-dependency-avoiding prototypes.
class EditorTabs;
class AssetTree;
namespace Ui {
  class MainWindow;
}


class TopLevelManager
{
public:
  TopLevelManager(Ui::MainWindow* ui_pointer);
  ~TopLevelManager();

  void show_error_message(QString text);
  void set_statusbar_message(QString text);
  EditorTabs* get_tab_widget();
  AssetTree* get_tree_widget();
  ProjectData* get_database();

private:
  Ui::MainWindow* ui;
  EditorTabs* editor_tabs_widget;
  AssetTree* asset_tree_widget;
  ProjectData* database;
};

