#include "assettree.h"
#include <QDrag>
#include <QMenu>
#include <QApplication>
#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <projectmanager.h>

AssetTree::AssetTree(QWidget* parent) : QTreeWidget(parent) {
  setMouseTracking(true);
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &AssetTree::customContextMenuRequested, this, &AssetTree::show_item_right_click_context_menu);
  connect(this, &AssetTree::itemDoubleClicked, this, &AssetTree::tree_item_double_click);
}

void AssetTree::showEvent(QShowEvent*) {
  auto rootItem = invisibleRootItem();
  rootItem->setFlags(rootItem->flags() ^ Qt::ItemIsDropEnabled);
  for(int i = 0; i < 6; i++)
    topLevelItem(i)->setFlags((topLevelItem(i)->flags() | Qt::ItemFlag::ItemIsDropEnabled) ^ Qt::ItemFlag::ItemIsDragEnabled);
}

/* Only let objects be dropped inside of
 * their respective top level items. */
void AssetTree::dropEvent(QDropEvent* event) {
  QList<QTreeWidgetItem*> kids = this->selectedItems();

  /* row number before the drag - initial position */
  if (kids.size() == 0) return;
  QTreeWidgetItem* parent = kids.at(0)->parent();

  /* perform the default implementation */
  QTreeWidget::dropEvent(event);

  /* get new index */
  QTreeWidgetItem* destination = kids.at(0)->parent();

  if(parent != destination) {
    destination->removeChild(kids.at(0));
    parent->addChild(kids.at(0));
  }

  printf("item drop: item[%s] from[%s] destination[%s]\n",
         kids.at(0)->text(0).toUtf8().data(),
         parent->text(0).toUtf8().data(),
         destination->text(0).toUtf8().data());

  if (!parent || !destination){
      event->setDropAction(Qt::IgnoreAction);
      return;
  }
}

void AssetTree::show_item_right_click_context_menu(const QPoint &pos) {
  // if TLI, have custom behaviour
  QTreeWidgetItem* item = itemAt(pos);

  auto add_action = [this](QString name, QMenu& context_menu, std::function<void()> func){
    QAction* new_action = new QAction(name, this);
    connect(new_action, &QAction::triggered, this, func);
    context_menu.addAction(new_action);
  };

  // item right click
  QMenu context_menu("Context menu", this);
  add_action("Right click menu", context_menu, [item](){
    printf("You clicked a button on the context menu for %s!\n", item->text(0).toUtf8().data());
  });
  context_menu.exec(mapToGlobal(pos));
}

void AssetTree::load_database_into_tree() {
  for(std::pair<int, AssetEntry*> kv : *ProjectData::fetch().get_db())
    add_asset_to_tree(kv.second);
}

void AssetTree::add_asset_to_tree(AssetEntry *entry) {
  add_child_to_tli(entry->type, entry->name);
  name_to_asset_id_map.insert({ entry->name, entry->id });
}

QTreeWidgetItem* AssetTree::add_child_to_tli(int tli_index, std::string name) {
  QTreeWidgetItem* toplvlitem = topLevelItem(tli_index);
  QTreeWidgetItem* child = new QTreeWidgetItem(toplvlitem, { name.c_str() });
  child->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
  child->sortChildren(0, Qt::SortOrder::AscendingOrder);
  toplvlitem->insertChild(-1, child);
  return child;
}

void AssetTree::clear_tree_children() {
  for(int i = 0; i < topLevelItemCount(); ++i) {
    int child_count = topLevelItem(i)->childCount();
    for(int j = 0; j < child_count; ++j) {
      QTreeWidgetItem* child = topLevelItem(i)->child(0);
      topLevelItem(i)->removeChild(child);
      delete child;
    }
  }
}

void AssetTree::tree_item_double_click(QTreeWidgetItem *item, int) {
  // if top level item
  if(!item->parent()) return;

  if(name_to_asset_id_map.count(item->text(0).toStdString()) <= 0)
    throw "Trying to fetch nonexistant item on double click";

  int id = name_to_asset_id_map.at(item->text(0).toStdString());

  GET_UI()->editorTabs->open_asset_in_tab(ProjectData::fetch().get_asset(id));
}
