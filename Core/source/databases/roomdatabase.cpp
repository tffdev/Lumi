#include "include/roomdatabase.h"
#include <filesystem.h>

RoomDatabase::RoomDatabase(BackgroundDatabase* background_db, TilesetDatabase* tileset_db) {
  assets = FileSystem::load_rooms(tileset_db, background_db);
  for(RoomAsset* asset : assets) {
    id_map.insert(std::pair<std::string, size_t>(asset->get_name(), asset->get_id()));
  }
}

RoomDatabase::~RoomDatabase() {
  for(RoomAsset* asset : assets) {
    delete asset;
  }
}

RoomAsset* RoomDatabase::get_room_by_id(size_t id) {
  return assets.at(id);
}

size_t RoomDatabase::get_room_id(std::string name) {
  return id_map.at(name);
}

bool RoomDatabase::room_exists(std::string name) {
  if(id_map.count(name) > 0) return true;
  return false;
}

size_t RoomDatabase::get_size() {
  return assets.size();
}
