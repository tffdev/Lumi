#include "assettree.h"
#include <QDrag>
#include <QMenu>
#include <QApplication>
#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <maindatamanager.h>

AssetTree::AssetTree(QWidget* parent) : QTreeWidget(parent) {
  setMouseTracking(true);
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &AssetTree::customContextMenuRequested,
          this, &AssetTree::show_item_right_click_context_menu);

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

  if(!item->parent()) {
    QMenu context_menu("Context menu", this);

    if(indexAt(pos).row() == 0) add_action("New Object", context_menu, [](){
      MainDataManager::fetch().new_asset_request(ProjectData::db().get_objects(), "object", 0);
    });

    if(indexAt(pos).row() == 1) add_action("New Sprite", context_menu, []{
      MainDataManager::fetch().new_asset_request(ProjectData::db().get_sprites(), "sprite", 1);
    });

    context_menu.exec(mapToGlobal(pos));
    for(QAction* action : context_menu.actions()) delete action;
    return;
  };

  // item right click
  QMenu context_menu("Context menu", this);
  QAction action_delete("Delete Asset", this);

  context_menu.addAction(&action_delete);
  context_menu.exec(mapToGlobal(pos));
}

template <typename T>
void AssetTree::insert_tree_items_from_database(int itemnum, Database<T>* db) {
  for(T asset : db->get_all_assets()) {
    add_child_to_tli(itemnum, asset.name);
  }
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

void AssetTree::load_database_into_tree() {
  clear_tree_children();
  insert_tree_items_from_database(0, &ProjectData::db().get_objects());
  insert_tree_items_from_database(1, &ProjectData::db().get_sprites());
  insert_tree_items_from_database(2, &ProjectData::db().get_backgrounds());
  insert_tree_items_from_database(3, &ProjectData::db().get_sounds());
  insert_tree_items_from_database(4, &ProjectData::db().get_tilesets());
  insert_tree_items_from_database(5, &ProjectData::db().get_rooms());

  // sort items
  for(int i=0; i < topLevelItemCount(); i++){
    topLevelItem(i)->sortChildren(0, Qt::SortOrder::AscendingOrder);
  }
}
