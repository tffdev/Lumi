#include "texturemanager.h"

TextureManager::TextureManager() {}
TextureManager::~TextureManager() { destroy_all(); }

/**
 * @brief Given the filepath of a texture, load that texture into this manager.
 * @param path The virtual filesystem path of the texture.
 */
void TextureManager::insert(std::string path) {
  textures.insert(std::pair<std::string, TextureAsset*>(path, new TextureAsset(path)));
}

/**
 * @brief Check if this manager contains an instance of the texture given a path.
 * @param path The virtual filesystem path of the texture.
 * @return True if this manager contains the texture, false otherwise.
 */
bool TextureManager::has_texture(std::string path) {
  std::map<std::string, TextureAsset*>::iterator it = textures.find(path);
  if (it != textures.end()) {
      return true;
  }
  return false;
}

/**
 * @brief Get a texture asset given the path to the texutre.
 * @param path The virtual filesystem path of the texture.
 * @return A TextureAsset reference.
 */
TextureAsset& TextureManager::get_texture(std::string path) {
  if(!has_texture(path))
    throw "Texture " + path + " doesn't exist!";

  return *textures.at(path);
}

/**
 * @brief Get the number of textures contained within this manager.
 * @return The number of textures as an integer.
 */
int TextureManager::get_textures_size() {
  return static_cast<int>(textures.size());
}

/**
 * @brief Free the video memory taken up by all textures within this manager and remove all references in the map.
 */
void TextureManager::destroy_all() {
  for (auto const& element : textures) {
    delete static_cast<TextureAsset*>(element.second);
  }
  textures.clear();
}
