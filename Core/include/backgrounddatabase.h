#pragma once
#include <backgroundasset.h>
#include <vector>
#include <map>

class BackgroundDatabase
{
public:
  BackgroundDatabase();
  size_t size();
  size_t get_id(std::string name);
  std::string get_name_from_id(size_t id);
  BackgroundAsset* get_asset(size_t id);
private:
  std::vector<BackgroundAsset*> backgrounds;
  std::map<std::string, size_t> id_map;
};
