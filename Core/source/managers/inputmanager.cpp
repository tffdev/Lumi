#include "inputmanager.h"
#include <algorithm>

InputManager::InputManager() {}

std::string string_to_lower(std::string data) {
  std::transform(data.begin(), data.end(), data.begin(), [](char in) -> char {
    if (in <= 'Z' && in >= 'A')
      return in - ('Z' - 'z');
    return in;
  });

  return data;
}

/**
 * @brief Passes an event into this manager to update the states of all keys.
 * @param e The SDL_Event to process.
 */
void InputManager::process_events(SDL_Event *e) {
  if(e->type == SDL_KEYDOWN && e->key.repeat == 0) {
    std::string keycode(string_to_lower(SDL_GetKeyName(e->key.keysym.sym)));
    insert_keyref_if_nonexistent(keycode);
    printf("Key %s pressed.\n", keycode.c_str());
    keystate_map.at(keycode).pressed = true;
    keystate_map.at(keycode).down = true;
    keystate_map.at(keycode).released = false;
  }

  if(e->type == SDL_KEYUP) {
    std::string keycode(string_to_lower(SDL_GetKeyName(e->key.keysym.sym)));
    insert_keyref_if_nonexistent(keycode);
    printf("Key %s released.\n", keycode.c_str());
    keystate_map.at(keycode).pressed = false;
    keystate_map.at(keycode).down = false;
    keystate_map.at(keycode).released = true;
  }
}


/**
 * @brief Returns the keystate struct attached to a keycode.
 * @param keycode The name of the key to get the state of.
 * @return A keystate struct.
 */
keystate InputManager::get_key_state(std::string keycode) {
  return keystate_map.at(string_to_lower(keycode));
}

/**
 * @brief Check if this manager's keystate map contains a key.
 * @param keycode The keycode as a string.
 * @return True if the key exists, false if not.
 */
bool InputManager::has_key(std::string keycode) {
  std::map<std::string, keystate>::iterator it = keystate_map.find(string_to_lower(keycode));
  if (it != keystate_map.end()) {
      return true;
  }
  return false;
}

/**
 * @brief Using a given keycode, inserts a key:value pair into the map with an empty (all false) keystate struct.
 * @param keycode The keycode name as a string.
 */
void InputManager::insert_keyref_if_nonexistent(std::string keycode) {
  if(!has_key(keycode)) {
      keystate_map.insert(std::pair<std::string, keystate>(string_to_lower(keycode), keystate{}));
  }
}

/**
 * @brief To be called after the frame ends, clear the "pressed" attribute of all keys.
 */
void InputManager::clear_pressed_keys() {
  std::map<std::string, keystate>::iterator it = keystate_map.begin();
  while (it != keystate_map.end()) {
    it->second.pressed = false;
    it->second.released = false;
    it++;
  }
}
