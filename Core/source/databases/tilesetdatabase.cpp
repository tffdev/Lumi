#include "tilesetdatabase.h"
#include <filesystem.h>

TilesetDatabase::TilesetDatabase() {
  assets = FileSystem::load_tilesets();
  for(TilesetAsset* asset : assets) {
    id_map.insert(std::pair<std::string, unsigned int>(asset->get_name(), asset->get_id()));
  }
}

unsigned long long TilesetDatabase::get_size() {
  return assets.size();
}

TilesetAsset* TilesetDatabase::get_asset(unsigned int id) {
  return assets.at(id);
}

unsigned int TilesetDatabase::get_id_from_name(std::string name) {
  return id_map.at(name);
}
