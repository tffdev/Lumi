#include "projectdata.h"

// Database utilities
bool ProjectData::asset_name_exists(std::string name) {
  return name_to_asset_map.count(name) > 0;
}

void ProjectData::rename_asset(std::string old_name, std::string new_name) {
  AssetEntry* entry = name_to_asset_map.at(old_name);
  name_to_asset_map.erase(old_name);
  name_to_asset_map.insert({new_name, entry});
}

bool ProjectData::asset_id_exists(int id) {
  return asset_db.count(id) > 0;
}

AssetEntry* ProjectData::get_asset(int id) {
  if(!asset_id_exists(id)) return nullptr;
  return asset_db.at(id);
}

void ProjectData::clear_database() {
  // delete all data at pointers
  for(std::pair<int, AssetEntry*> kv : asset_db) delete kv.second;

  // clear maps
  asset_db.clear();
  name_to_asset_map.clear();
}

void ProjectData::load_entries_into_db(pugi::xml_node &root, std::string subset_name, ASSET_TYPE type) {
  for(pugi::xml_node& node : root.child(subset_name.c_str()).children()){
      AssetEntry* asset = new AssetEntry;
      asset->id = generate_new_unique_id();
      asset->node = node;
      asset->type = type;
      asset->name = asset->name = node.attribute("name").as_string();
      asset_db.insert({asset->id, asset});
      name_to_asset_map.insert({asset->name, asset});
  }
}

// get new ID
int ProjectData::generate_new_unique_id() {
  int id = static_cast<int>(asset_db.size());
  do {
    id++;
  } while (asset_db.count(id) > 0);
  return id;
}

bool ProjectData::load_project_file_into_database(std::string path) {
  clear_database();

  pugi::xml_parse_result result = doc.load_file(path.c_str());
  if (result) {
    printf("Parsed project %s without errors!\n", path.c_str());
  }else{
    printf("Error: %s at %lld", result.description(), result.offset);
    return false;
  }

  pugi::xml_node root_node = doc.child("project");

  // load project name
  game_name = root_node.child("name").text().as_string();

  // Load project into databases
  load_entries_into_db(root_node, "objects",     ASSET_TYPE::OBJECT);
  load_entries_into_db(root_node, "sounds",      ASSET_TYPE::SOUND);
  load_entries_into_db(root_node, "sprites",     ASSET_TYPE::SPRITE);
  load_entries_into_db(root_node, "tilesets",    ASSET_TYPE::TILESET);
  load_entries_into_db(root_node, "backgrounds", ASSET_TYPE::BACKGROUND);
  load_entries_into_db(root_node, "rooms",       ASSET_TYPE::ROOM);

  printf("Loaded database. Size: %i\n", asset_db.size());

  // load config
  config_node = root_node.child("window");

  return true;
}

std::unordered_map<int, AssetEntry*>* ProjectData::get_db() {
  return &asset_db;
}
