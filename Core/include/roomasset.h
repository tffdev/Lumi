#pragma once
#include <string>
#include <mathlibrary.h>
#include <vector>
#include <backgroundasset.h>

struct RoomTile {
  int x;
  int y;
  int width;
  int height;
  int texture_x;
  int texture_y;
  size_t tileset_ref;
};

struct RoomTileLayer {
  std::vector<RoomTile> tiles;
  int depth;
};

struct RoomBackground {
  size_t asset_ref;
  int depth;
  double offset_x;
  double offset_y;
};

class RoomAsset
{
public:
  RoomAsset(size_t id,
            std::string name,
            std::string creation_code,
            size_t size_x,
            size_t size_y,
            std::vector<RoomTileLayer> tile_layers,
            std::vector<RoomBackground> backgrounds);

  size_t get_id();
  Vector2<size_t> get_size();
  std::string get_name();
  std::string get_creation_code();
  unsigned long long get_tile_layer_size();
  std::vector<RoomTileLayer> get_tile_layers();
  std::vector<RoomBackground> get_backgrounds();
  RoomTileLayer get_tile_layer(unsigned int layer);
  RoomBackground get_background(unsigned int layer);
private:
  size_t id;
  std::string name;
  std::string creation_code;
  Vector2<size_t> size;
  std::vector<RoomTileLayer> room_tile_layers;
  std::vector<RoomBackground> room_backgrounds;
};
