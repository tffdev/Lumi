#include "include/backgrounddatabase.h"
#include <filesystem.h>

BackgroundDatabase::BackgroundDatabase() {
  backgrounds = FileSystem::load_backgrounds();
  for(BackgroundAsset* asset : backgrounds) {
    id_map.insert(std::pair<std::string, size_t>(asset->get_name(), asset->get_id()));
  }
}

unsigned long long BackgroundDatabase::size() {
  return backgrounds.size();
}

size_t BackgroundDatabase::get_id(std::string name) {
  return id_map.at(name);
}

std::string BackgroundDatabase::get_name_from_id(size_t id) {
  return backgrounds.at(id)->get_name();
}

BackgroundAsset* BackgroundDatabase::get_asset(size_t id) {
  return backgrounds.at(id);
}
