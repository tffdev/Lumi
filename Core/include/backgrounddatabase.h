#pragma once
#include <backgroundasset.h>
#include <vector>
#include <map>

class BackgroundDatabase
{
public:
  BackgroundDatabase();
  unsigned long long size();
  unsigned long long get_id(std::string name);
  std::string get_name_from_id(unsigned long long id);
  BackgroundAsset* get_asset(unsigned long long id);
private:
  std::vector<BackgroundAsset*> backgrounds;
  std::map<std::string, unsigned long long> id_map;
};

/*
  BackgroundDatabase bg_db;
  CHECK_EQ(bg_db.size(), 1);
  CHECK_EQ(bg_db.get_id("backgroundTest"), 0);
  CHECK_EQ(bg_db.get_name_from_id(0).compare("backgroundTest"), 0);
  */
