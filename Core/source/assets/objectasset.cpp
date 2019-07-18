#include "include/objectasset.h"

/**
 * @brief Create an instance of ObjectAsset which contains all data needed to create an instance
 * within Lua-space.
 * @param id The ID to attach to the object.
 * @param name The name to attach to the object.
 * @param default_sprite The name of the sprite of an object.
 * @param code A string containing the Lua code of an object.
 */
ObjectAsset::ObjectAsset(int id, std::string name, std::string default_sprite, std::string code)
  : id(id),
    name(name),
    default_sprite(default_sprite),
    code(code) {}

/**
 * @brief Check if this object has a default sprite.
 * @return True if it has a default sprite, false otherwise.
 */
bool ObjectAsset::has_default_sprite() {
  return default_sprite.compare("") != 0;
}

/**
 * @brief Check if the object has Lua code attached to it.
 * @return True if the object has code, false otherwise.
 */
bool ObjectAsset::has_code() {
  return code.compare("") != 0;
}

/**
 * @brief Get the name of this object.
 * @return Object's name as a string.
 */
std::string ObjectAsset::get_name() {
  return name;
}

/**
 * @brief Get the ID of this object.
 * @return Object's ID as integer.
 */
int ObjectAsset::get_id() {
  return id;
}

/**
 * @brief Get the default sprite name of this object.
 * @return Sprite name as a string.
 */
std::string ObjectAsset::get_default_sprite() {
  return default_sprite;
}

/**
 * @brief Get the Lua code contained in this object.
 * @return The Lua code of this object as a string.
 */
std::string ObjectAsset::get_code() {
  return code;
}
