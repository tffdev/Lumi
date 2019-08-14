#include "tilesetdatabase.h"
#include <filesystem.h>

TilesetDatabase::TilesetDatabase() {
  assets = FileSystem::load_tilesets();
  for(TilesetAsset* asset : assets) {
    id_map.insert(std::pair<std::string, size_t>(asset->get_name(), asset->get_id()));
  }
}

size_t TilesetDatabase::get_size() {
  return assets.size();
}

TilesetAsset* TilesetDatabase::get_asset(size_t id) {
  return assets.at(id);
}

TilesetAsset* TilesetDatabase::get_asset(std::string name) {
  return assets.at(get_id_from_name(name));
}

size_t TilesetDatabase::get_id_from_name(std::string name) {
  std::map<std::string, size_t>::iterator it = id_map.find(name);
  if(it != id_map.end()) {
     return id_map.at(name);
  }
  throw "Can't find tileset " + name;
}
