#pragma once
#include <string>
#include <vector>
#include <external/pugixml.hpp>
using namespace std;

enum ASSET_TYPE {
  OBJECT,
  SPRITE,
  BACKGROUND,
  SOUND,
  TILESET,
  ROOM,
};

struct AssetEntry {
  int id;
  ASSET_TYPE type;
  std::string name;
  pugi::xml_node* node;
};

// Basic math stuff
struct Vector2 {
  int x;
  int y;
};

//////////////// Components of top-level assets //////////////
// Room components
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

struct RoomInstance {
  string name;
  Vector2 position;
};

struct RoomBackground {
  int depth;
  Vector2 offset;
  string image;
};

// Sprite Components
struct HitboxAsset {
  size_t shape;
  Vector2 offset;
  Vector2 size;
};

struct Subimage {
  Vector2 texture_pos;
  Vector2 size;
};

/////////////////////// Top-level assets ///////////////////////
struct GenericTopLevelAsset {
  string name;
  ASSET_TYPE asset_type;
};

struct ObjectAsset : GenericTopLevelAsset {
  string sprite_name;
  bool persistent;
  string code;
};

struct BackgroundAsset : GenericTopLevelAsset {
  string path;
};

struct RoomAsset : GenericTopLevelAsset {
  Vector2 size;
  string creation_code;
  vector<RoomInstance> instances;
  vector<TileLayer> tile_layers;
  vector<BackgroundAsset> backgrounds;
};

struct SoundAsset : GenericTopLevelAsset {
  string path;
};

struct SpriteAsset : GenericTopLevelAsset {
  Vector2 size;
  Vector2 origin;
  string texture_path;
  HitboxAsset hitbox;
  vector<Subimage> subimages;
};

struct TilesetAsset : GenericTopLevelAsset {
  string texture_path;
  Vector2 tile_size;
};

// Config is its own thing
struct Configuration {
  string title;
  Vector2 size;
  double scale;
  uint32_t background_color;
  size_t fps;
};
