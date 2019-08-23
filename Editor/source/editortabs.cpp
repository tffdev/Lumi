#include "include/editortabs.h"
#include <objecteditor.h>

EditorTabs::EditorTabs(QWidget* parent) : QTabWidget(parent) {
}

void EditorTabs::close_tab(int index) {
  QWidget* w = widget(index);
  int id = map_asset_tab_to_id.at(w);

  // remove from both maps
  map_asset_tab_to_id.erase(w);
  map_asset_id_to_tab.erase(id);

  removeTab(index);
}

void EditorTabs::open_asset_in_tab(AssetEntry *asset) {

  // If asset is already open
  if(map_asset_id_to_tab.count(asset->id) > 0) {
    setCurrentWidget(map_asset_id_to_tab.at(asset->id));
    return;
  }

  // Create tab
  QWidget* widget;

  // Depending on the asset's type, create a different kind of editor widget.
  switch(asset->type) {
    case ASSET_TYPE::OBJECT: widget = new ObjectEditor(); break;
    // add more cases here
    default: widget = new QWidget();
  }

  map_asset_id_to_tab.insert({asset->id, widget});
  map_asset_tab_to_id.insert({widget, asset->id});
  addTab(widget, asset->name.c_str());

  // switch to that tab
  setCurrentWidget(widget);
}
