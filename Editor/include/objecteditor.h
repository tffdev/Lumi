#pragma once
#include <QWidget>
#include <projectdata.h>

namespace Ui {
  class ObjectEditor;
}

class ObjectEditor : public QWidget
{
  Q_OBJECT

public:
  explicit ObjectEditor(AssetEntry* asset, QWidget *parent = nullptr);
  ~ObjectEditor();
public slots:
  void save_asset();

private:
  Ui::ObjectEditor *ui;
  AssetEntry* held_asset;
};
