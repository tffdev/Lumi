#pragma once
#include <SFML/Window.hpp>
#include <map>
#include <stdio.h>

typedef struct {
  bool pressed;
  bool down;
  bool released;
} keystate;

class InputManager
{
public:
  InputManager();
  void pass_event(sf::Event&);
private:
  std::map<std::string, keystate> pressed_map;
};
