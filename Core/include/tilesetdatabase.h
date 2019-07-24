#pragma once
#include <tilesetasset.h>
#include <vector>
#include <map>

class TilesetDatabase
{
public:
  TilesetDatabase();
  TilesetAsset* get_asset(unsigned int id);
  unsigned int get_id_from_name(std::string name);
  unsigned long long get_size();
private:
  std::vector<TilesetAsset*> assets;
  std::map<std::string, unsigned int> id_map;

};
