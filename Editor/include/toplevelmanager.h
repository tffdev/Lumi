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

/**
 * Manages project-level utility and special window events such as
 * showing error messages.
 */
class TopLevelManager : public QObject
{
public:
  TopLevelManager(Ui::MainWindow* ui_pointer);
  virtual ~TopLevelManager();

  // Special window events
  void show_error_message(QString text);
  void show_statusbar_message(QString text);

  void open_config_tab();
  void open_asset_at_tree_item(QTreeWidgetItem* item, int);

  void set_modified_since_last_save(bool);
  bool has_been_modified_since_last_save();

  bool run_current_project();

  // Getters
  EditorTabs* get_tab_widget();
  AssetTree* get_tree_widget();
  ProjectData* get_database();

private:
  // Container for frequently-used front-end elements.
  Ui::MainWindow* ui;
  EditorTabs* editor_tabs_widget;
  AssetTree* asset_tree_widget;

  // Database containing all current project data
  ProjectData* database;

  // Store whether the project has been modified since the last save
  bool modified_since_last_save;
};

