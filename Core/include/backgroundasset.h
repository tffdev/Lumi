#pragma once
#include <textureasset.h>

class BackgroundAsset
{
public:
  BackgroundAsset(unsigned long long id, std::string name, TextureAsset* texture);
  ~BackgroundAsset();
  unsigned long long get_id();
  std::string get_name();
  TextureAsset* get_texture_asset();
private:
  unsigned long long id;
  std::string name;
  TextureAsset* texture;
};
