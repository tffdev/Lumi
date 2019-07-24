#include "include/roomasset.h"

RoomAsset::RoomAsset(std::string name,
          std::string creation_code,
          unsigned int size_x,
          unsigned int size_y,
          std::vector<RoomTileLayer> tile_layers,
          std::vector<RoomBackground> backgrounds)
  : name(name),
    creation_code(creation_code),
    size(size_x, size_y),
    room_tile_layers(tile_layers),
    room_backgrounds(backgrounds) {}

Vector2<unsigned int> RoomAsset::get_size() {
  return size;
}

std::string RoomAsset::get_name() {
  return name;
}

std::string RoomAsset::get_creation_code() {
  return creation_code;
}

RoomBackground RoomAsset::get_background(unsigned int layer) {
  return room_backgrounds.at(layer);
}

RoomTileLayer RoomAsset::get_tile_layer(unsigned int layer) {
  return room_tile_layers.at(layer);
}
