#include "luamanager.h"
#include <lualibrary.h>

/**
 * @brief Instantiates a Lua state and processes the "main.lua" and "objects.lua" boilerplate code files within the state.
 */
LuaManager::LuaManager() {
  L = luaL_newstate();
  luaL_openlibs(L);

  // load boilerplate code
  if(luaL_dostring(L, FileSystem::read_file("main.lua").c_str()) != 0)
    throw "Error loading main.lua:\n" + std::string(lua_tostring(L, -1));
}

/**
 * @brief Execute a string of Lua code within the attached state.
 * @param str The Lua code to execute.
 */
int LuaManager::execute(std::string str) {
  return luaL_dostring(L, str.c_str());
}

int LuaManager::load_object_code(ObjectDatabase *database) {
  execute("__lumi_system.containers.object_code = {}");
  for(ObjectAsset* object : database->get_all_object_assets()){

    int err = execute("__lumi_system.containers.object_code["+std::to_string(object->get_id()+1)+"] = function()\n" + object->get_code() + "\nend");
    if(err != LUA_OK) return err;
  }
  return LUA_OK;
}

/**
 * @brief Get an integer from the Lua state within the global scope.
 * @param name The name of the global variable.
 * @return The integer value stored in that variable.
 */
int LuaManager::get_global_int(std::string name) {
  lua_getglobal(L, name.c_str());
  return static_cast<int>(lua_tonumber(L, -1));
}

/**
 * @brief Get an double (default 'number') from the Lua state within the global scope.
 * @param name The name of the global variable.
 * @return The double value stored in that variable.
 */
double LuaManager::get_global_double(std::string name) {
  lua_getglobal(L, name.c_str());
  return lua_tonumber(L, -1);
}

/**
 * @brief Run the "update" closure on all instances.
 */
int LuaManager::run_update_function() {
  lua_getglobal(L, "__lumi_system");
  lua_getfield(L, -1, "process_update");
  return lua_pcall(L, 0, 0, 0);
}

/**
 * @brief Run the "draw" closure on all instances.
 */
int LuaManager::run_draw_function() {
  lua_getglobal(L, "__lumi_system");
  lua_getfield(L, -1, "process_draw");
  return lua_pcall(L, 0, 0, 0);
}

/**
 * @brief Get the number of instances that currently exist in Lua-space.
 * @return The amount of instances as an integer.
 */
int LuaManager::get_instance_count() {
  lua_getglobal(L, "__lumi_system");
  lua_getfield(L, -1, "containers");
  lua_getfield(L, -1, "instances");
  lua_len(L, -1);
  int len = static_cast<int>(lua_tointeger(L, -1));
  return len;
}

/**
 * @brief Makes a C function globally callable from Lua.
 * @param func The function to attach.
 * @param name The name to give the function in Lua-space.
 * @return Nil
 */
int LuaManager::register_function(lua_CFunction func, std::string name) {
  lua_register(L, name.c_str(), func);
  return 0;
}

/**
 * @brief Makes a C function callable from Lua and contains the function within the "__lumi_system" table.
 * @param func The function to attach.
 * @param name The name to give the function in Lua-space within the "__lumi_system" table.
 * @return Nil
 */
int LuaManager::register_lumi_system_function(lua_CFunction func, std::string name) {
  lua_getglobal(L, "__lumi_system");
  lua_pushstring(L, name.c_str());
  lua_pushcfunction(L, func);
  lua_settable(L, -3);
  return 0;
}

int LuaManager::register_lumi_library_function(lua_CFunction func, std::string name) {
  lua_getglobal(L, "__lumi_system");
  lua_getfield(L, -1, "c_library");
  lua_pushstring(L, name.c_str());
  lua_pushcfunction(L, func);
  lua_settable(L, -3);
  return 0;
}

/**
 * @brief Get the Lua_State object attached to this manager.
 * @return A Lua_State object.
 */
lua_State* LuaManager::get_lua_state() {
  return L;
}

/**
 * @brief Pushes pointers to essential engine components into Lua-space, letting the components be manipulated within LuaLibrary C-like functions.
 * @param objdatabase The engine's instance of ObjectDatabase.
 * @param window_manager The engine's instance of WindowManager.
 * @param sprite_database The engine's instance of SpriteDatabase.
 */
void LuaManager::assign_state_containers(ObjectDatabase* objdatabase,
                                         WindowManager* window_manager,
                                         SpriteDatabase* sprite_database,
                                         InputManager* input_manager,
                                         AudioDatabase* audio_database,
                                         RoomManager* room_manager) {
  lua_pushstring(L, "object_database");
  lua_pushlightuserdata(L, objdatabase);
  lua_settable(L, LUA_REGISTRYINDEX);

  lua_pushstring(L, "sprite_database");
  lua_pushlightuserdata(L, sprite_database);
  lua_settable(L, LUA_REGISTRYINDEX);

  lua_pushstring(L, "window_manager");
  lua_pushlightuserdata(L, window_manager);
  lua_settable(L, LUA_REGISTRYINDEX);

  lua_pushstring(L, "input_manager");
  lua_pushlightuserdata(L, input_manager);
  lua_settable(L, LUA_REGISTRYINDEX);

  lua_pushstring(L, "audio_database");
  lua_pushlightuserdata(L, audio_database);
  lua_settable(L, LUA_REGISTRYINDEX);

  lua_pushstring(L, "room_manager");
  lua_pushlightuserdata(L, room_manager);
  lua_settable(L, LUA_REGISTRYINDEX);
}

/**
 * @brief Load all LuaLibrary C functions into the attached Lua state.
 * @param objdatabase The engine's instance of ObjectDatabase.
 * @param window_manager The engine's instance of WindowManager.
 * @param sprite_database The engine's instance of SpriteDatabase.
 */
void LuaManager::load_library(ObjectDatabase* object_database,
                              WindowManager* window_manager,
                              SpriteDatabase* sprite_database,
                              InputManager* input_manager,
                              AudioDatabase* audio_database,
                              RoomManager* room_manager) {

  // Register Lua state variablse
  assign_state_containers(object_database, window_manager, sprite_database, input_manager, audio_database, room_manager);

  // Register global functions
  register_function(LuaLibrary::lua_library_test, "lua_library_test");

  // Register c_library functions
  register_lumi_library_function(LuaLibrary::lua_draw_sprite, "draw_sprite");
  register_lumi_library_function(LuaLibrary::lua_key_pressed, "key_pressed");
  register_lumi_library_function(LuaLibrary::lua_key_down, "key_down");
  register_lumi_library_function(LuaLibrary::lua_key_released, "key_released");
  register_lumi_library_function(LuaLibrary::lua_audio_play, "audio_play");
  register_lumi_library_function(LuaLibrary::lua_audio_stop, "audio_stop");
  register_lumi_library_function(LuaLibrary::lua_set_room, "set_room");

  // Register __lumi_system functions
  register_lumi_system_function(LuaLibrary::lumi_system_test, "lumi_system_test");
  register_lumi_system_function(LuaLibrary::lumi_system_get_asset_id, "get_asset_id");
  register_lumi_system_function(LuaLibrary::lumi_system_process_in_environment, "process_in_environment");
}

/**
 * @brief Get the number of cached object instantiation closures contained within Lua-space.
 * @return The number of object closures as an int.
 */
int LuaManager::object_code_length() {
  lua_getglobal(L, "__lumi_system");
  lua_getfield(L, -1, "containers");
  lua_getfield(L, -1, "object_code");
  lua_len(L, -1);
  return static_cast<int>(lua_tointeger(L, -1));
}

std::string LuaManager::get_error(ObjectDatabase* obj_database) {
  /*
   * TODO: Let this function format the string into something more easily readable.
   */
  //push custom error string
  if(lua_isstring(L, -1))
    last_error = lua_tostring(L, -1);
  else
    last_error = "Unknown error.";

  // IF THE ERROR IS AN OBJECT CODE ERROR
  if(last_error.substr(0, 46).compare("[string \"__lumi_system.containers.object_code[") == 0) {
    last_error.replace(0, 46, "");
    size_t obj_number_id_end = last_error.find_first_of(']');
    std::string object_name = obj_database->get_object_name( std::atoi(last_error.substr(0, obj_number_id_end).c_str()) - 1);
    last_error.replace(0, last_error.find_first_of(':') + 1, "");
    int line_num = std::atoi(last_error.substr(0, last_error.find_first_of(':')).c_str());
    last_error.replace(0, last_error.find_first_of(':') + 2, "");

    std::string error_string = last_error;
    std::stringstream err_stream;
    err_stream << "Error in object `" << object_name << "` line " << std::to_string(line_num-1) << ":\n" << error_string;
    last_error = err_stream.str();
  }

  // IF THE ERROR IS A ROOM CREATION CODE ERROR
  if(last_error.substr(0, 18).compare("[string \"-- ROOM [") == 0) {
    last_error.replace(0, 18, "");
    size_t obj_number_id_end = last_error.find_first_of(']');
    std::string room_name = last_error.substr(0, obj_number_id_end).c_str();
    last_error.replace(0, last_error.find_first_of(':') + 1, "");
    int line_num = std::atoi(last_error.substr(0, last_error.find_first_of(':')).c_str());
    last_error.replace(0, last_error.find_first_of(':') + 2, "");

    std::string error_string = last_error;
    std::stringstream err_stream;
    err_stream << "Error in room `" << room_name << "` creation code line " << std::to_string(line_num-1) << ":\n" << error_string;
    last_error = err_stream.str();
  }


  printf("%s\n", last_error.c_str());
  return last_error;
}
