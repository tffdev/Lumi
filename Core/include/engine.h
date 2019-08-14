#pragma once
#include <stdio.h>
#include <filesystem.h>
#include <objectasset.h>
#include <luamanager.h>
#include <configmanager.h>
#include <objectdatabase.h>
#include <lualibrary.h>
#include <windowmanager.h>

class LumiEngine
{
public:
  LumiEngine();
  void run();
private:
  ConfigManager  conf;
  WindowManager  window_manager;
  InputManager   input_manager;
  ObjectDatabase obj_database;
  SpriteDatabase spr_database;
  AudioDatabase  audio_database;
  LuaManager     lmanager;
  RoomManager    room_manager;
};
