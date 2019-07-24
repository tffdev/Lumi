#include "tilesetasset.h"

TilesetAsset::TilesetAsset(unsigned int id, std::string name, std::string path) : id(id), name(name), texture(path) {}

TextureAsset* TilesetAsset::get_texture() {
  return &texture;
}

unsigned int TilesetAsset::get_id() {
  return id;
}

std::string TilesetAsset::get_name() {
  return name;
}
