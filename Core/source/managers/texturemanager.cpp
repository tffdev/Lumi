#include "texturemanager.h"

TextureManager::TextureManager() {}

void TextureManager::insert(std::string path, TextureAsset asset) {
  textures.insert(std::pair<std::string, TextureAsset>(path, asset));
}

bool TextureManager::has_texture(std::string path) {
  std::map<std::string, TextureAsset>::iterator it = textures.find(path);
  if (it != textures.end()) {
      return true;
  }
  return false;
}

TextureAsset& TextureManager::get_texture(std::string path) {
  if(!has_texture(path))
    throw "Texture " + path + " doesn't exist!";

  return textures.at(path);
}
