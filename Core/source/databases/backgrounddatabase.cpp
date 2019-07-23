#include "include/backgrounddatabase.h"
#include <filesystem.h>

BackgroundDatabase::BackgroundDatabase() {
  backgrounds = FileSystem::load_backgrounds();
  for(BackgroundAsset* asset : backgrounds) {
    id_map.insert(std::pair<std::string, unsigned long long>(asset->get_name(), asset->get_id()));
  }
}

unsigned long long BackgroundDatabase::size() {
  return backgrounds.size();
}

unsigned long long BackgroundDatabase::get_id(std::string name) {
  return id_map.at(name);
}

std::string BackgroundDatabase::get_name_from_id(unsigned long long id) {
  return backgrounds.at(id)->get_name();
}

BackgroundAsset* BackgroundDatabase::get_asset(unsigned long long id) {
  return backgrounds.at(id);
}
