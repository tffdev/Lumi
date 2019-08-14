#include "tilesetasset.h"

TilesetAsset::TilesetAsset(size_t id, std::string name, std::string path) : id(id), name(name), texture(path) {}

TextureAsset* TilesetAsset::get_texture() {
  return &texture;
}

size_t TilesetAsset::get_id() {
  return id;
}

std::string TilesetAsset::get_name() {
  return name;
}
