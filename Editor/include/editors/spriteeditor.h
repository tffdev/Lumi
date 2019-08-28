#pragma once
#include <QWidget>
#include <asset_types.h>
#include <projectdata.h>
#include <toplevelmanager.h>

namespace Ui {
  class SpriteEditor;
}

class SpriteEditor : public QWidget
{
  Q_OBJECT

public:
  explicit SpriteEditor(TopLevelManager* tlm, AssetEntry* asset, QWidget *parent = nullptr);
  ~SpriteEditor();

private:
  Ui::SpriteEditor *ui;
  AssetEntry* held_asset;
  TopLevelManager* tlm;
};

