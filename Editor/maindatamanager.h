#pragma once
#include <ui_mainwindow.h>
#include <generic_database.h>
#include <projectdata.h>
#include <objecteditor.h>

class MainDataManager
{
public:
  // singleton stuff
  static MainDataManager& fetch() {
    static MainDataManager instance;
    return instance;
  }
  MainDataManager() {}
  MainDataManager(MainDataManager const&);

  void pass_ui(Ui::MainWindow* ui);
  Ui::MainWindow* get_ui();

private:
  Ui::MainWindow* ui;

public:
  template <typename T>
  std::string new_asset_request(Database<T>& db, std::string prefix, int tli_index) {
    printf("inserting new %s!\n", prefix.c_str());

    // Scan for first available name
    std::string name;
    size_t i = db.size();
    do {
        name = prefix + "_" + std::to_string(i);
        i++;
    } while(ProjectData::db().asset_name_exists(name));
    T asset;
    asset.name = name;
    db.insert_asset(name, asset);

    get_ui()->assetTree->topLevelItem(tli_index)->setExpanded(true);
    get_ui()->assetTree->topLevelItem(tli_index)->setSelected(false);
    get_ui()->assetTree->add_child_to_tli(tli_index, name)->setSelected(true);

    int index = get_ui()->editorTabs->addTab(new ObjectEditor(), name.c_str());
    get_ui()->editorTabs->setCurrentIndex(index);

    return name;
  }
};

