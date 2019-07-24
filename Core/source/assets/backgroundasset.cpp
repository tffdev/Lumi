#include "include/backgroundasset.h"

BackgroundAsset::BackgroundAsset(unsigned long long id, std::string name, TextureAsset& texture)
  : id(id), name(name), texture(texture) {}

unsigned long long BackgroundAsset::get_id() {
  return id;
}

std::string BackgroundAsset::get_name() {
  return name;
}

TextureAsset& BackgroundAsset::get_texture_asset() {
  return texture;
}
