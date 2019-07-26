#pragma once
#include <roomasset.h>
#include <map>
#include <backgrounddatabase.h>
#include <tilesetdatabase.h>

class RoomDatabase
{
public:
  RoomDatabase(BackgroundDatabase* background_db, TilesetDatabase* tileset_db);
  ~RoomDatabase();
  RoomAsset* get_asset(unsigned int id);
  unsigned int get_id_from_name(std::string name);
  unsigned long long get_size();
private:
  std::vector<RoomAsset*> assets;
  std::map<std::string, unsigned int> id_map;
};
