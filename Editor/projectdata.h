#pragma once
#include <generic_database.h>
#include <asset_types.h>
#include <external/pugixml.hpp>

class ProjectData
{
public:
  bool load_project_file_into_db(std::string path);
  Database<ObjectAsset> objects;
  Database<RoomAsset> rooms;
  Database<SoundAsset> sounds;
  Database<SpriteAsset> sprites;
  Database<BackgroundAsset> backgrounds;
  Database<TilesetAsset> tilesets;
  std::string game_name;
private:
  std::string last_parsing_error;
  void clear_all();
  void load_objects(pugi::xml_node& root);
  void load_rooms(pugi::xml_node& root);
  void load_sounds(pugi::xml_node& root);
  void load_sprites(pugi::xml_node& root);
  void load_backgrounds(pugi::xml_node& root);
  void load_tilesets(pugi::xml_node& root);
};
