#include "textureasset.h"
#include "filesystem.h"

TextureAsset::TextureAsset(std::string path): path(path) {
  std::string str = FileSystem::read_file(path, true);

  if(!texture.loadFromMemory(str.c_str(), str.size() * sizeof(char)))
    throw "Can't load texture " + path + " from memory";
}

/**
 * Only load texture into memory if it is needed by a sprite.
 * Have something to de-allocate textures in certain circumstances.
 * (Time-based?)
 */
sf::Texture* TextureAsset::get_texture_data() {
  return &texture;
}

Vector2<unsigned int> TextureAsset::get_size() {
  sf::Texture* tex = get_texture_data();
  return Vector2<unsigned int>(tex->getSize().x, tex->getSize().y);
}
