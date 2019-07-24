#include "include/roomdatabase.h"
#include <filesystem.h>

RoomDatabase::RoomDatabase(BackgroundDatabase* background_db, TilesetDatabase* tileset_db) {
  assets = FileSystem::load_rooms(tileset_db, background_db);
  for(RoomAsset* asset : assets) {
    id_map.insert(std::pair<std::string, unsigned int>(asset->get_name(), asset->get_id()));
  }
}

RoomAsset* RoomDatabase::get_asset(unsigned int id) {
  return assets.at(id);
}

unsigned int RoomDatabase::get_id_from_name(std::string name) {
  return id_map.at(name);
}

unsigned long long RoomDatabase::get_size() {
  return assets.size();
}
