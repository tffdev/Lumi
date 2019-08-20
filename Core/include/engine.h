#pragma once
#define SDL_MAIN_HANDLED
#include <windowmanager.h>
#include <luamanager.h>

class LumiEngine
{
public:
  LumiEngine();
  void run();
private:
  WindowManager  window_manager;
  InputManager   input_manager;
  ObjectDatabase obj_database;
  SpriteDatabase spr_database;
  AudioDatabase  audio_database;
  LuaManager     lmanager;
  RoomManager    room_manager;
};
