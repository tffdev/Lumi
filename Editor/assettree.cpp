#include "assettree.h"
#include <QDrag>

AssetTree::AssetTree(QWidget* parent) : QTreeWidget(parent) {
  connect(this, &AssetTree::itemPressed, this, &AssetTree::itemAssetPressed);
  setMouseTracking(true);
}

void AssetTree::showEvent(QShowEvent*) {
  auto rootItem = invisibleRootItem();
  rootItem->setFlags( rootItem->flags() ^ Qt::ItemIsDropEnabled );
  for(int i = 0; i < 6; i++)
    topLevelItem(i)->setFlags((topLevelItem(i)->flags() | Qt::ItemFlag::ItemIsDropEnabled) ^ Qt::ItemFlag::ItemIsDragEnabled);
}

void AssetTree::itemAssetPressed(QTreeWidgetItem* item, int) {
  if(!item->parent()) return; // top level, ignore
  printf("Item was pressed: %s\n", item->text(0).toUtf8().data());
}

/*
 * Only let objects be dropped inside of
 * their respective top level items.
 */
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
