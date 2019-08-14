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
  void set_room(size_t);
  size_t get_current_room_id();
  RoomAsset* get_current_room();
  void draw_tiles(WindowManager* win_manager);
  void draw_backgrounds(WindowManager* win_manager);
  RoomDatabase* get_room_database();
  size_t get_default_room_id();
private:
  size_t default_room_id;
  RoomAsset* current_room;
  TilesetDatabase tileset_database;
  BackgroundDatabase background_database;
  RoomDatabase room_database;
};
