#include "luamanager.h"
#include <lualibrary.h>

LuaManager::LuaManager() {
  L = luaL_newstate();
  luaL_openlibs(L);

  if(luaL_dostring(L, FileSystem::read_file("main.lua").c_str()) != 0)
    throw "Error loading main.lua:\n" + std::string(lua_tostring(L, -1));

  if(luaL_dostring(L, FileSystem::read_file("objects.lua").c_str()) != 0)
    throw "Error loading objects.lua:\n" + std::string(lua_tostring(L, -1));
}

void LuaManager::execute(std::string str) {
  int err = luaL_dostring(L, str.c_str());
  if(err == 1)
    throw "Error executing Lua string:\n" + std::string(lua_tostring(L, -1));
}

int LuaManager::get_global_int(std::string name) {
  lua_getglobal(L, name.c_str());
  return static_cast<int>(lua_tonumber(L, -1));
}

void LuaManager::run_update_function() {
  lua_getglobal(L, "__luma_system");
  lua_getfield(L, -1, "process_update");
  lua_pcall(L, 0, 0, 0);
}

void LuaManager::run_draw_function() {
  int top = lua_gettop(L);
  lua_getglobal(L, "__luma_system");
  lua_getfield(L, -1, "process_draw");
  lua_pcall(L, 0, 0, 0);
  lua_settop(L, top);
}

int LuaManager::get_instance_count() {
  lua_getglobal(L, "__luma_system");
  lua_getfield(L, -1, "containers");
  lua_getfield(L, -1, "instances");
  lua_len(L, -1);
  int len = static_cast<int>(lua_tointeger(L, -1));
  return len;
}

int LuaManager::register_function(lua_CFunction func, std::string name) {
  lua_register(L, name.c_str(), func);
  return 0;
}

int LuaManager::register_luma_system_function(lua_CFunction func, std::string name) {
  lua_getglobal(L, "__luma_system");
  lua_pushstring(L, name.c_str());
  lua_pushcfunction(L, func);
  lua_settable(L, -3);
  return 0;
}

lua_State* LuaManager::get_lua_state() {
  return L;
}

void LuaManager::assign_state_containers(ObjectDatabase* objdatabase, WindowManager* window_manager) {
  lua_pushstring(L, "object_database");  /* push value */
  lua_pushlightuserdata(L, objdatabase);  /* push address */
  /* registry.object_database = pointer*/
  lua_settable(L, LUA_REGISTRYINDEX);

  lua_pushstring(L, "window_manager");
  lua_pushlightuserdata(L, window_manager);
  lua_settable(L, LUA_REGISTRYINDEX);
}

void LuaManager::load_library(ObjectDatabase* object_database, WindowManager* window_manager) {
  // Register Lua state variablse
  assign_state_containers(object_database, window_manager);

  // Register global functions
  register_function(LuaLibrary::lua_library_test, "lua_library_test");
  register_function(LuaLibrary::lua_draw_square, "draw_square");

  // Register __luma_system functions
  register_luma_system_function(LuaLibrary::luma_system_test, "luma_system_test");
  register_luma_system_function(LuaLibrary::luma_system_get_object_id, "get_object_id");
  register_luma_system_function(LuaLibrary::luma_system_process_in_environment, "process_in_environment");
}

int LuaManager::object_code_length() {
  lua_getglobal(L, "__luma_system");
  lua_getfield(L, -1, "containers");
  lua_getfield(L, -1, "object_code");
  lua_len(L, -1);
  return static_cast<int>(lua_tointeger(L, -1));
}
