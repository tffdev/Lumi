#pragma once
#include <QTreeWidget>
#include <QDropEvent>
#include <QMimeData>

class AssetTree : public QTreeWidget
{
public:
  AssetTree(QWidget* parent);
  void dropEvent(QDropEvent* event);
  void showEvent(QShowEvent* event);
private slots:
  void mouseMoveEvent(QMouseEvent* event);
  void mousePressEvent(QMouseEvent* event);
  void itemDroppedSlot(QTreeWidgetItem* item, int col);
};
