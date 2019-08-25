#include "include/editortabs.h"
#include <objecteditor.h>
#include <configurationeditor.h>

EditorTabs::EditorTabs(QWidget* parent) : QTabWidget(parent) {
  connect(this, &EditorTabs::tabCloseRequested, this, &EditorTabs::close_tab);
}

void EditorTabs::set_tlm(TopLevelManager *input_tlm) {
  tlm = input_tlm;
}

void EditorTabs::close_all_tabs() {
  clear();
  map_asset_id_to_tab.clear();
  map_asset_tab_to_id.clear();
}

void EditorTabs::close_tab(int index) {
  QWidget* w = widget(index);

  int id = map_asset_tab_to_id.at(w);

  // remove from both maps
  map_asset_tab_to_id.erase(w);
  map_asset_id_to_tab.erase(id);

  removeTab(index);
  delete w;
}

void EditorTabs::rename_tab(int asset_id, std::string new_name) {
  QWidget* w = map_asset_id_to_tab.at(asset_id);
  setTabText(indexOf(w), new_name.c_str());
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
    case ASSET_TYPE::OBJECT: widget = new ObjectEditor(tlm, asset); break;
    // add more cases here
    default: widget = new QWidget();
  }

  // insert into two-way map
  map_asset_id_to_tab.insert({asset->id, widget});
  map_asset_tab_to_id.insert({widget, asset->id});

  addTab(widget, asset->name.c_str());

  // switch to that tab
  setCurrentWidget(widget);
}

void EditorTabs::open_config_tab(pugi::xml_node* conf_node) {
  // if it's already open
  if(map_asset_id_to_tab.count(-1) > 0) {
    setCurrentWidget(map_asset_id_to_tab.at(-1));
    return;
  }

  // not open, make new config editor
  QWidget* w = new ConfigurationEditor(tlm, conf_node);
  addTab(w, "Project Settings");
  setCurrentWidget(w);

  map_asset_id_to_tab.insert({-1, w});
  map_asset_tab_to_id.insert({w, -1});
}
