#include "spritedatabase.h"

SpriteDatabase::SpriteDatabase() {
    sprites = FileSystem::load_sprites(texture_manager);
    int i = 0;
    for(SpriteAsset asset : sprites) {
      id_map.insert(std::pair<std::string, int>(asset.get_name(), i));
      i++;
    }
}

sf::Sprite SpriteDatabase::get_sprite_by_id(unsigned long long id, int subimage) {
  try {
    return sprites.at(id).get_subimage(subimage);
  } catch (...) {
    throw "Can't find sprite id " + std::to_string(id);
  }
}

bool SpriteDatabase::sprite_exists(std::string name) {
  std::map<std::string,int>::iterator it = id_map.find(name);
  if(it != id_map.end()) {
    return true;
  }
  return false;
}

int SpriteDatabase::get_sprite_id(std::string name) {
  if(!sprite_exists(name)) throw "Sprite " + name + " does not exist.";
  return id_map.at(name);
}
