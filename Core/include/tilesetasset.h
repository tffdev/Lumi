#pragma once
#include <textureasset.h>
#include <mathlibrary.h>

class TilesetAsset
{
public:
  TilesetAsset(unsigned int id, std::string name, std::string path);
  TextureAsset* get_texture();
  unsigned int get_id();
  std::string get_name();
private:
  unsigned int id;
  std::string name;
  TextureAsset texture;
};
