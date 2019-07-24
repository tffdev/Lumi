#pragma once
#include <backgroundasset.h>
#include <vector>
#include <map>

class BackgroundDatabase
{
public:
  BackgroundDatabase();
  unsigned long long size();
  unsigned int get_id(std::string name);
  std::string get_name_from_id(unsigned int id);
  BackgroundAsset* get_asset(unsigned int id);
private:
  std::vector<BackgroundAsset*> backgrounds;
  std::map<std::string, unsigned int> id_map;
};
