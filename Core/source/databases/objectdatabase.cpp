#include "include/objectdatabase.h"

/**
 * @brief Create an instance of ObjectDatabase, loading all objects defined in `objects.xml`,
 * using the FileSystem module to load in the objects. Creates a mapping of object_name -> ID.
 */
ObjectDatabase::ObjectDatabase() {
  object_assets = FileSystem::load_objects();
  for(ObjectAsset* obj : object_assets){
      object_name_id_map.insert(std::pair<std::string, int>(obj->get_name(), obj->get_id()));
    }
}

/**
 * @brief Gets the name of an object given the object's ID.
 * @param id The ID of an object.
 * @return A string containing the name of the object. An empty string if the object doesn't exist.
 */
std::string ObjectDatabase::get_object_name(size_t id) {
  try {
    return object_assets.at(id)->get_name();
  } catch (...) {
    return "";
  }
}

/**
 * @brief Get the ID of an object given the object's name.
 * @param name The name of an object.
 * @return The integer ID of the object.
 */
size_t ObjectDatabase::get_object_id(std::string name) {
    if(!object_name_exists(name)) throw "Object " + name + " doesn't exist.";
    return object_name_id_map.at(name);
}

/**
 * @brief Get the Lua code attached to an object.
 * @param id
 * @return The Lua code for an object as a string. Returns an empty string if the object doesn't exist.
 */
std::string ObjectDatabase::get_object_code(size_t id) {
  try {
    return object_assets.at(id)->get_code();
  } catch (...) {
    return "";
  }
}

/**
 * @brief Checks if an object with the given name exists.
 * @param name The name of an object.
 * @return Returns true if an object with the given name exists. False otherwise.
 */
bool ObjectDatabase::object_name_exists(std::string name) {
  return (object_name_id_map.count(name) == 0) ? false : true;
}

/**
 * @brief Checks if an object with the given ID exists.
 * @param id The ID of an object.
 * @return Returns true if an object with the given ID exists. False otherwise.
 */
bool ObjectDatabase::object_id_exists(size_t id) {
  try {
    return (object_assets.at(id)) ? true : false;
  } catch (...) {
    return false;
  }
}

/**
 * @brief Get the pointers of all objects contained within this instance of ObjectDatabase.
 * @return A vector containing pointers to many ObjectAssets.
 */
std::vector<ObjectAsset*> ObjectDatabase::get_all_object_assets() {
  return object_assets;
}
