#include "luamanager.h"
#include <lualibrary.h>

/**
 * @brief Instantiates a Lua state and processes the "main.lua" and "objects.lua" boilerplate code files within the state.
 */
LuaManager::LuaManager() {
  L = luaL_newstate();
  luaL_openlibs(L);

  if(luaL_dostring(L, FileSystem::read_file("main.lua").c_str()) != 0)
    throw "Error loading main.lua:\n" + std::string(lua_tostring(L, -1));

  if(luaL_dostring(L, FileSystem::read_file("objects.lua").c_str()) != 0)
    throw "Error loading objects.lua:\n" + std::string(lua_tostring(L, -1));
}

/**
 * @brief Execute a string of Lua code within the attached state.
 * @param str The Lua code to execute.
 */
void LuaManager::execute(std::string str) {
  int err = luaL_dostring(L, str.c_str());
  if(err == 1)
    throw "Error executing Lua string:\n" + std::string(lua_tostring(L, -1));
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
 * @brief Run the "update" closure on all instances.
 */
void LuaManager::run_update_function() {
  lua_getglobal(L, "__luma_system");
  lua_getfield(L, -1, "process_update");
  lua_pcall(L, 0, 0, 0);
}

/**
 * @brief Run the "draw" closure on all instances.
 */
void LuaManager::run_draw_function() {
  int top = lua_gettop(L);
  lua_getglobal(L, "__luma_system");
  lua_getfield(L, -1, "process_draw");
  lua_pcall(L, 0, 0, 0);
  lua_settop(L, top);
}

/**
 * @brief Get the number of instances that currently exist in Lua-space.
 * @return The amount of instances as an integer.
 */
int LuaManager::get_instance_count() {
  lua_getglobal(L, "__luma_system");
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
 * @brief Makes a C function callable from Lua and contains the function within the "__luma_system" table.
 * @param func The function to attach.
 * @param name The name to give the function in Lua-space within the "__luma_system" table.
 * @return Nil
 */
int LuaManager::register_luma_system_function(lua_CFunction func, std::string name) {
  lua_getglobal(L, "__luma_system");
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
void LuaManager::assign_state_containers(ObjectDatabase* objdatabase, WindowManager* window_manager, SpriteDatabase* sprite_database) {
  lua_pushstring(L, "object_database");  /* push value */
  lua_pushlightuserdata(L, objdatabase);  /* push address */
  /* registry.object_database = pointer*/
  lua_settable(L, LUA_REGISTRYINDEX);

  lua_pushstring(L, "sprite_database");
  lua_pushlightuserdata(L, sprite_database);
  lua_settable(L, LUA_REGISTRYINDEX);

  lua_pushstring(L, "window_manager");
  lua_pushlightuserdata(L, window_manager);
  lua_settable(L, LUA_REGISTRYINDEX);
}

/**
 * @brief Load all LuaLibrary C functions into the attached Lua state.
 * @param objdatabase The engine's instance of ObjectDatabase.
 * @param window_manager The engine's instance of WindowManager.
 * @param sprite_database The engine's instance of SpriteDatabase.
 */
void LuaManager::load_library(ObjectDatabase* object_database, WindowManager* window_manager, SpriteDatabase* sprite_database) {
  // Register Lua state variablse
  assign_state_containers(object_database, window_manager, sprite_database);

  // Register global functions
  register_function(LuaLibrary::lua_library_test, "lua_library_test");
  register_function(LuaLibrary::lua_draw_sprite, "draw_sprite");

  // Register __luma_system functions
  register_luma_system_function(LuaLibrary::luma_system_test, "luma_system_test");
  register_luma_system_function(LuaLibrary::luma_system_get_object_id, "get_object_id");
  register_luma_system_function(LuaLibrary::luma_system_get_sprite_id, "get_sprite_id");
  register_luma_system_function(LuaLibrary::luma_system_process_in_environment, "process_in_environment");
}

/**
 * @brief Get the number of cached object instantiation closures contained within Lua-space.
 * @return The number of object closures as an int.
 */
int LuaManager::object_code_length() {
  lua_getglobal(L, "__luma_system");
  lua_getfield(L, -1, "containers");
  lua_getfield(L, -1, "object_code");
  lua_len(L, -1);
  return static_cast<int>(lua_tointeger(L, -1));
}
