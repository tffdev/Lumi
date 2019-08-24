#pragma once
#include <QTabWidget>
#include <unordered_map>
#include <projectdata.h>

class EditorTabs : public QTabWidget
{
public:
  EditorTabs(QWidget* parent);

  void open_asset_in_tab(AssetEntry* asset);
  void rename_tab(int asset_id, std::string new_name);
  void open_config_tab();

public slots:
  void close_tab(int index);
  void close_all_tabs();
  std::unordered_map<int, QWidget*> map_asset_id_to_tab;
  std::unordered_map<QWidget*, int> map_asset_tab_to_id;
};
