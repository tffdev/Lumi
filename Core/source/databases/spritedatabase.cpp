#include "spritedatabase.h"

/**
 * @brief Create an instance of SpriteDatabase. Using the FileSystem module, this loads all sprites into
 * the sprites vector and all texture paths referenced in `sprites.xml` into this object's instance of TextureManager.
 */
SpriteDatabase::SpriteDatabase() {
    sprites = FileSystem::load_sprites();
    int i = 0;
    for(SpriteAsset* asset : sprites) {
      id_map.insert(std::pair<std::string, size_t>(asset->get_name(), i));
      i++;
    }
}

SpriteDatabase::~SpriteDatabase() {
  for(SpriteAsset* asset : sprites) {
    delete asset;
  }
}

/**
 * @brief Gets a sprite asset by ID.
 * @param id The ID of the sprite.
 * @return A pointer to a SpriteAsset.
 */
SpriteAsset* SpriteDatabase::get_sprite_by_id(size_t id) {
  try {
    return sprites.at(id);
  } catch (...) {
    throw "Can't find sprite id " + std::to_string(id);
  }
}

/**
 * @brief Checks if a sprite with a given name exists.
 * @param name The name of a sprite.
 * @return True if a sprite with the given name exists, false otherwise.
 */
bool SpriteDatabase::sprite_exists(std::string name) {
  std::map<std::string,size_t>::iterator it = id_map.find(name);
  if(it != id_map.end()) {
    return true;
  }
  return false;
}

/**
 * @brief Given a name, returns the integer ID of that sprite asset.
 * @param name The name of a sprite.
 * @return The ID of a sprite.
 */
size_t SpriteDatabase::get_sprite_id(std::string name) {
  if(!sprite_exists(name)) throw "Sprite " + name + " does not exist.";
  return id_map.at(name);
}
