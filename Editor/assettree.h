#pragma once
#include <QTreeWidget>
#include <QDropEvent>
#include <QMimeData>
#include <generic_database.h>

class AssetTree : public QTreeWidget
{
public:
  AssetTree(QWidget* parent);
  void dropEvent(QDropEvent* event);
  void showEvent(QShowEvent* event);

  template <typename T>
  void insert_tree_items_from_database(int itemnum, Database<T>* db);
  void load_database_into_tree();
  void clear_tree_children();
  QTreeWidgetItem* add_child_to_tli(int tli_index, std::string name);

private slots:
  void show_item_right_click_context_menu(const QPoint &pos);
  template <typename T>
  std::string new_asset_request(Database<T>& db, std::string prefix);
};
