#include "include/backgroundasset.h"

BackgroundAsset::BackgroundAsset(size_t id, std::string name, TextureAsset* texture)
  : id(id), name(name), texture(texture) {}

BackgroundAsset::~BackgroundAsset() {
  delete texture;
}

size_t BackgroundAsset::get_id() {
  return id;
}

std::string BackgroundAsset::get_name() {
  return name;
}

TextureAsset* BackgroundAsset::get_texture_asset() {
  return texture;
}
