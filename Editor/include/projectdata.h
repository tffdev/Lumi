#pragma once
#include <QString>
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
  ProjectData();
  ~ProjectData();

  // Project loading and saving
  QString get_current_project_file_directory();
  QString get_current_project_file_name();
  bool save_current_project_to_file(QString path);
  bool load_project_file_into_database(QString path);
  void create_new_project();
  pugi::xml_document& get_project_xml_document();
  std::string get_project_xml_as_string();

  // Asset manipulation
  AssetEntry* get_asset(int id);
  bool asset_name_exists(std::string name);
  bool asset_id_exists(int id);
  void rename_asset(std::string old_name, std::string new_name);

  // Database stuff
  std::unordered_map<int, AssetEntry*>* get_map();

  // Utility
  pugi::xml_node* get_config_node();
  int generate_new_unique_id();

  void clear_database();
  void load_entries_into_db(pugi::xml_node &root, QString rootname, ASSET_TYPE type);
  void load_entry_into_db(pugi::xml_node& node, ASSET_TYPE type);

  void set_name_and_dir_from_path(QString path);

private:
  // Data perterning to the current loaded project
  pugi::xml_document project_xml_document;
  pugi::xml_node config_node;
  std::unordered_map<int, AssetEntry*> asset_db;
  std::unordered_map<std::string, AssetEntry*> name_to_asset_map;

  // Current loaded project metadata (file location etc)
  QString game_name;
  QString current_loaded_file_directory;
  QString current_loaded_file_name;
};
