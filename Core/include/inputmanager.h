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
  bool key_pressed(std::string);
  bool key_down(std::string);
  bool key_released(std::string);
  std::string get_key_name(const sf::Keyboard::Key key);
private:
  std::map<std::string, keystate> pressed_map;
};
