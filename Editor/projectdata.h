#pragma once
#include <generic_database.h>
#include <asset_types.h>
#include <external/pugixml.hpp>

class ProjectData
{
public:
  // singleton stuff
  static ProjectData& db() {
    static ProjectData instance;
    return instance;
  }

  bool load_project_file_into_databases(std::string path);

  bool asset_name_exists(std::string name);

  std::string game_name;
  Configuration config;

  Database<ObjectAsset>& get_objects();
  Database<RoomAsset>& get_rooms();
  Database<SoundAsset>& get_sounds();
  Database<SpriteAsset>& get_sprites();
  Database<BackgroundAsset>& get_backgrounds();
  Database<TilesetAsset>& get_tilesets();

private:
  // singleton stuff
  ProjectData() {}
  ProjectData(ProjectData const&);

  std::string last_parsing_error;
  void clear_all_databases();
  void load_objects_from_xml(pugi::xml_node& root);
  void load_rooms_from_xml(pugi::xml_node& root);
  void load_sounds_from_xml(pugi::xml_node& root);
  void load_sprites_from_xml(pugi::xml_node& root);
  void load_backgrounds_from_xml(pugi::xml_node& root);
  void load_tilesets_from_xml(pugi::xml_node& root);
  void load_config_from_xml(pugi::xml_node& root);

  Database<ObjectAsset> objects;
  Database<RoomAsset> rooms;
  Database<SoundAsset> sounds;
  Database<SpriteAsset> sprites;
  Database<BackgroundAsset> backgrounds;
  Database<TilesetAsset> tilesets;
};
