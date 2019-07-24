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
  int asset_ref;
  int depth;
  double offset_x;
  double offset_y;
};

class RoomAsset
{
public:
  RoomAsset(std::string name,
            std::string creation_code,
            unsigned int size_x,
            unsigned int size_y,
            std::vector<RoomTileLayer> tile_layers,
            std::vector<RoomBackground> backgrounds);
  RoomTileLayer get_tile_layer(unsigned int layer);
  Vector2<unsigned int> get_size();
  std::string get_name();
  std::string get_creation_code();
  RoomBackground get_background(unsigned int layer);
private:
  std::string name;
  std::string creation_code;
  Vector2<unsigned int> size;
  std::vector<RoomTileLayer> room_tile_layers;
  std::vector<RoomBackground> room_backgrounds;
};