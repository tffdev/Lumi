#pragma once
#include <roomasset.h>
#include <tilesetasset.h>
#include <roomdatabase.h>
#include <tilesetdatabase.h>
#include <windowmanager.h>

class RoomManager
{
public:
  RoomManager();
  void set_room(unsigned long long);
  unsigned int get_current_room_id();
  RoomAsset* get_current_room();
  void draw_tiles(WindowManager* win_manager);
  void draw_backgrounds(WindowManager* win_manager);
  RoomDatabase* get_room_database();
private:
  unsigned int default_room_id;
  RoomAsset* current_room;
  TilesetDatabase tileset_database;
  BackgroundDatabase background_database;
  RoomDatabase room_database;
};
