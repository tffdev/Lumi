#pragma once
#include <tilesetasset.h>
#include <vector>
#include <map>

class TilesetDatabase
{
public:
  TilesetDatabase();
  TilesetAsset* get_asset(size_t id);
  TilesetAsset* get_asset(std::string name);
  size_t get_id_from_name(std::string name);
  size_t get_size();
private:
  std::vector<TilesetAsset*> assets;
  std::map<std::string, size_t> id_map;

};
