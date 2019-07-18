#pragma once
#include <map>
#include <stdio.h>
#include <SDL2/SDL.h>

typedef struct {
  bool pressed = false;
  bool down = false;
  bool released = false;
} keystate;

class InputManager
{
public:
  InputManager();
  void process_events(SDL_Event* e);
  bool has_key(std::string keycode);
  void insert_keyref_if_nonexistent(std::string keycode);
  void clear_pressed_keys();
  keystate get_key_state(std::string keycode);
private:
  std::map<std::string, keystate> keystate_map;
};
