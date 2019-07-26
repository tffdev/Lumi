#include "tilesetdatabase.h"
#include <filesystem.h>

TilesetDatabase::TilesetDatabase() {
  assets = FileSystem::load_tilesets();
  for(TilesetAsset* asset : assets) {
    printf("inserting into map: %s\n", asset->get_name().c_str());
    id_map.insert(std::pair<std::string, unsigned int>(asset->get_name(), asset->get_id()));
  }
}

unsigned long long TilesetDatabase::get_size() {
  return assets.size();
}

TilesetAsset* TilesetDatabase::get_asset(unsigned int id) {
  return assets.at(id);
}

TilesetAsset* TilesetDatabase::get_asset(std::string name) {
  return assets.at(get_id_from_name(name));
}

unsigned int TilesetDatabase::get_id_from_name(std::string name) {
  printf("getting name: %s\n", name.c_str());
  std::map<std::string, unsigned int>::iterator it = id_map.find(name);
  if(it != id_map.end()) {
     return id_map.at(name);
  }
  throw "Can't find name";
}
