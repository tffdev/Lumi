#include "include/roomdatabase.h"
#include <filesystem.h>

RoomDatabase::RoomDatabase(BackgroundDatabase* background_db, TilesetDatabase* tileset_db) {
  assets = FileSystem::load_rooms(tileset_db, background_db);
  for(RoomAsset* asset : assets) {
    id_map.insert(std::pair<std::string, unsigned int>(asset->get_name(), asset->get_id()));
  }
}

RoomDatabase::~RoomDatabase() {
  for(RoomAsset* asset : assets) {
    delete asset;
  }
}

RoomAsset* RoomDatabase::get_asset(unsigned long long id) {
  return assets.at(id);
}

unsigned long long RoomDatabase::get_room_id(std::string name) {
  return id_map.at(name);
}

bool RoomDatabase::room_exists(std::string name) {
  if(id_map.count(name) > 0) return true;
  return false;
}

unsigned long long RoomDatabase::get_size() {
  return assets.size();
}
