#pragma once
#include <asset_types.h>
#include <unordered_map>
#include <projectdata.h>
#include <QTreeWidget>
#include <QDropEvent>
#include <toplevelmanager.h>

class AssetTree : public QTreeWidget
{
public:
  AssetTree(QWidget* parent);

  void set_tlm(TopLevelManager* tlm);

  void dropEvent(QDropEvent* event);
  void showEvent(QShowEvent* event);

  void load_database_into_tree(ProjectData* db);
  void clear_tree_children();
  void add_asset_to_tree(AssetEntry* entry);
  QTreeWidgetItem* add_child_to_tli(int tli_index, std::string name);

  void rename_tree_item(int asset_id, std::string new_name);

  int get_item_id_at_widget(QTreeWidgetItem* item);
  QTreeWidgetItem* get_widget_from_item_id(int id);

private slots:
  void show_item_right_click_context_menu(const QPoint &pos);

private:
  TopLevelManager* tlm;
  std::unordered_map<QTreeWidgetItem*, int> widget_to_asset_id_map;
  std::unordered_map<int, QTreeWidgetItem*> asset_id_to_widget_map;
};
