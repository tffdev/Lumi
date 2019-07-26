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
  unsigned int tileset_ref;
};

struct RoomTileLayer {
  std::vector<RoomTile> tiles;
  int depth;
};

struct RoomBackground {
  unsigned int asset_ref;
  int depth;
  double offset_x;
  double offset_y;
};

class RoomAsset
{
public:
  RoomAsset(unsigned int id,
            std::string name,
            std::string creation_code,
            unsigned int size_x,
            unsigned int size_y,
            std::vector<RoomTileLayer> tile_layers,
            std::vector<RoomBackground> backgrounds);

  unsigned int get_id();
  Vector2<unsigned int> get_size();
  std::string get_name();
  std::string get_creation_code();
  unsigned long long get_tile_layer_size();
  std::vector<RoomTileLayer> get_tile_layers();
  std::vector<RoomBackground> get_backgrounds();
  RoomTileLayer get_tile_layer(unsigned int layer);
  RoomBackground get_background(unsigned int layer);
private:
  unsigned int id;
  std::string name;
  std::string creation_code;
  Vector2<unsigned int> size;
  std::vector<RoomTileLayer> room_tile_layers;
  std::vector<RoomBackground> room_backgrounds;
};
