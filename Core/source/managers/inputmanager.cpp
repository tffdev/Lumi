#include "inputmanager.h"

InputManager::InputManager() {}

char asciitolower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

void InputManager::pass_event(sf::Event& e) {
  if(e.type == sf::Event::KeyPressed) {
      std::string data = get_key_name(e.key.code).c_str();
      std::transform(data.begin(), data.end(), data.begin(), asciitolower);
      printf("char: %s\n", data.c_str());
    }
}
