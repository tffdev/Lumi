#pragma once
#include <QTreeWidget>
#include <QDropEvent>
#include <QMimeData>
#include <asset_types.h>
#include <projectdata.h>

class AssetTree : public QTreeWidget
{
public:
  AssetTree(QWidget* parent);
  void dropEvent(QDropEvent* event);
  void showEvent(QShowEvent* event);

  void load_database_into_tree(std::unordered_map<int, AssetEntry*> db);
  void clear_tree_children();
  void add_asset_to_tree(AssetEntry* entry);
  QTreeWidgetItem* add_child_to_tli(int tli_index, std::string name);

  void item_double_click(QTreeWidgetItem* item, int);

private slots:
  void show_item_right_click_context_menu(const QPoint &pos);

  std::unordered_map<std::string, int> name_to_asset_id_map;
};
