#pragma once
#include <QWidget>
#include <projectdata.h>
#include <toplevelmanager.h>
#include <editortabs.h>
#include <assettree.h>

namespace Ui {
  class ObjectEditor;
}

class ObjectEditor : public QWidget
{
  Q_OBJECT

public:
  explicit ObjectEditor(TopLevelManager* tlm, AssetEntry* asset, QWidget *parent = nullptr);
  ~ObjectEditor();

public slots:
  void save_asset();

private:
  Ui::ObjectEditor *ui;
  AssetEntry* held_asset;
  TopLevelManager* tlm;
};
