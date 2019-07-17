#include "texturemanager.h"

TextureManager::TextureManager() {}
TextureManager::~TextureManager() { destroy_all(); }

void TextureManager::insert(std::string path) {
  textures.insert(std::pair<std::string, TextureAsset*>(path, new TextureAsset(path)));
}

bool TextureManager::has_texture(std::string path) {
  std::map<std::string, TextureAsset*>::iterator it = textures.find(path);
  if (it != textures.end()) {
      return true;
  }
  return false;
}

TextureAsset& TextureManager::get_texture(std::string path) {
  if(!has_texture(path))
    throw "Texture " + path + " doesn't exist!";

  return *textures.at(path);
}

int TextureManager::get_textures_size() {
  return static_cast<int>(textures.size());
}

void TextureManager::destroy_all() {
  for (auto const& element : textures) {
    delete static_cast<TextureAsset*>(element.second);
  }
  textures.clear();
}
