#include "spritedatabase.h"

SpriteDatabase::SpriteDatabase() {
    sprites = FileSystem::load_sprites(texture_manager);
    int i = 0;
    for(SpriteAsset asset : sprites) {
      id_map.insert(std::pair<std::string, int>(asset.get_name(), i));
      i++;
    }
}

SpriteAsset* SpriteDatabase::get_sprite_by_id(unsigned long long id) {
  try {
    return &sprites.at(id);
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

TextureManager& SpriteDatabase::get_texture_manager() {
  return texture_manager;
}
