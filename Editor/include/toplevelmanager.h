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


class TopLevelManager : public QObject
{

public:
  TopLevelManager(Ui::MainWindow* ui_pointer);
  virtual ~TopLevelManager();

  void show_error_message(QString text);
  void show_statusbar_message(QString text);
  EditorTabs* get_tab_widget();
  AssetTree* get_tree_widget();
  ProjectData* get_database();
  bool create_new_asset(ASSET_TYPE type);

  void set_modified_since_last_save(bool);
  bool has_been_modified_since_last_save();
  bool run_current_project();
  void open_config_tab();
  void open_asset_at_tree_item(QTreeWidgetItem* item, int);

private:
  Ui::MainWindow* ui;
  EditorTabs* editor_tabs_widget;
  AssetTree* asset_tree_widget;
  ProjectData* database;

  // Store whether the project has been modified since the last save
  bool modified_since_last_save;
};

