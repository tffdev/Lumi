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
  RoomAsset* get_asset(unsigned long long id);
  unsigned long long get_room_id(std::string name);
  bool room_exists(std::string name);
  unsigned long long get_size();
private:
  std::vector<RoomAsset*> assets;
  std::map<std::string, unsigned long long> id_map;
};
