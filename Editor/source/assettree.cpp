#include "assettree.h"
#include <QDrag>
#include <QMenu>
#include <QApplication>

AssetTree::AssetTree(QWidget* parent) : QTreeWidget(parent) {
  setMouseTracking(true);
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &AssetTree::customContextMenuRequested, this, &AssetTree::show_item_right_click_context_menu);
}

void AssetTree::set_tlm(TopLevelManager *input_tlm) {
  tlm = input_tlm;
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

void AssetTree::load_database_into_tree(ProjectData* db) {
  // clear tree then insert all assets from the object database
  clear_tree_children();
  for(std::pair<int, AssetEntry*> kv : *(db->get_map()))
    add_asset_to_tree(kv.second);
}

void AssetTree::add_asset_to_tree(AssetEntry *entry) {
  QTreeWidgetItem* item_reference = add_child_to_tli(entry->type, entry->name);
  widget_to_asset_id_map.insert({ item_reference, entry->id });
  asset_id_to_widget_map.insert({ entry->id, item_reference });
}

void AssetTree::rename_tree_item(int asset_id, std::string new_name) {
  QTreeWidgetItem* item_reference = asset_id_to_widget_map.at(asset_id);
  item_reference->setText(0, QString(new_name.c_str()));
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

int AssetTree::get_item_id_at_widget(QTreeWidgetItem* item) {
  return widget_to_asset_id_map.at(item);
}

QTreeWidgetItem* AssetTree::get_widget_from_item_id(int id) {
  return asset_id_to_widget_map.at(id);
}
