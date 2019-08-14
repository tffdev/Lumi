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
  RoomAsset* get_room_by_id(size_t id);
  size_t get_room_id(std::string name);
  bool room_exists(std::string name);
  size_t get_size();
private:
  std::vector<RoomAsset*> assets;
  std::map<std::string, size_t> id_map;
};
