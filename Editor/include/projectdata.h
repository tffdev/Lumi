#pragma once
#include <unordered_map>
#include <asset_types.h>
#include <external/pugixml.hpp>

/*
 * ProjectData
 * ==================
 * Database containing all assets.
 * Map: Integer identifier -> XML node
 * The integer identifier will allow things to be renamed easier.
 */

class ProjectData
{
public:
  // singleton stuff
  static ProjectData& fetch() {
    static ProjectData instance;
    return instance;
  }

  bool asset_name_exists(std::string name);
  bool asset_id_exists(int id);

  AssetEntry* get_asset(int id);
  std::unordered_map<int, AssetEntry*>* get_db();
  pugi::xml_node* get_config_node();

  bool load_project_file_into_database(std::string path);
  int generate_new_unique_id();

  void rename_asset(std::string old_name, std::string new_name);

private:
  // singleton stuff
  ProjectData() {}
  ProjectData(ProjectData const&);

  void clear_database();
  void load_entries_into_db(pugi::xml_node &root, std::string rootname, ASSET_TYPE type);

  void load_entry_into_db(pugi::xml_node& node, ASSET_TYPE type);

  std::string game_name;

  std::unordered_map<int, AssetEntry*> asset_db;
  std::unordered_map<std::string, AssetEntry*> name_to_asset_map;

  pugi::xml_node config_node;

  pugi::xml_document doc;
};
