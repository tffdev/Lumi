#pragma once
#include <string>
#include <vector>
using namespace std;

struct Vector2 {
  int x;
  int y;
};

struct ObjectAsset {
  string name;
  string sprite_name;
  bool persistent;
  string code;
};

/* Rooms */
struct Tile {
  Vector2 position;
  Vector2 size;
  Vector2 texture_position;
  string tileset_name;
};

struct TileLayer {
  string name;
  int depth;
  vector<Tile> tiles;
};

struct BackgroundAsset {
  string name;
  string path;
};

struct RoomInstance {
  std::string name;
  Vector2 position;
};

struct RoomBackground {
  int depth;
  Vector2 offset;
  std::string image;
};

struct RoomAsset {
  string name;
  Vector2 size;
  string creation_code;
  vector<RoomInstance> instances;
  vector<TileLayer> tile_layers;
  vector<BackgroundAsset> backgrounds;
};

struct SoundAsset {
  string name;
  string path;
};

struct HitboxAsset {
  size_t shape;
  Vector2 offset;
  Vector2 size;
};

struct Subimage {
  Vector2 texture_pos;
  Vector2 size;
};

struct SpriteAsset {
  string name;
  Vector2 size;
  Vector2 origin;
  string texture_path;
  HitboxAsset hitbox;
  vector<Subimage> subimages;
};

struct TilesetAsset {
  string name;
  string texture_path;
  Vector2 tile_size;
};

struct Configuration {
  string title;
  Vector2 size;
  double scale;
  uint32_t background_color;
  size_t fps;
};
