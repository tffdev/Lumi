#include "include/roomasset.h"

RoomAsset::RoomAsset(size_t id,
          std::string name,
          std::string creation_code,
          size_t size_x,
          size_t size_y,
          std::vector<RoomTileLayer> tile_layers,
          std::vector<RoomBackground> backgrounds,
          std::vector<InstancePlacement> instance_placements)
  : id(id),
    name(name),
    creation_code(creation_code),
    size(size_x, size_y),
    room_tile_layers(tile_layers),
    room_backgrounds(backgrounds),
    instance_placements(instance_placements) {}

Vector2<size_t> RoomAsset::get_size() {
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

size_t RoomAsset::get_id() {
  return id;
}

size_t RoomAsset::get_tile_layer_size() {
  return room_tile_layers.size();
}

std::vector<RoomTileLayer> RoomAsset::get_tile_layers() {
  return room_tile_layers;
}
std::vector<RoomBackground> RoomAsset::get_backgrounds() {
  return room_backgrounds;
}

std::vector<InstancePlacement> RoomAsset::get_instance_placements() {
  return instance_placements;
}
