#pragma once
#include <textureasset.h>
#include <mathlibrary.h>

class TilesetAsset
{
public:
  TilesetAsset(size_t id, std::string name, std::string path);
  TextureAsset* get_texture();
  size_t get_id();
  std::string get_name();
private:
  size_t id;
  std::string name;
  TextureAsset texture;
};
