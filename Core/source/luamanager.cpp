#include "include/luamanager.h"

LuaManager::LuaManager() {
    L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dostring(L, FileSystem::read_file("main.lua").c_str());
    luaL_dostring(L, FileSystem::read_file("objects.lua").c_str());
}

void LuaManager::execute(std::string str) {
    luaL_dostring(L, str.c_str());
}

int LuaManager::get_global_int(std::string name) {
    lua_getglobal(L, name.c_str());
    return static_cast<int>(lua_tonumber(L, -1));
}
