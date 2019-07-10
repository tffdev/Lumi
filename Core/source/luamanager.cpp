#include "luamanager.h"

LuaManager::LuaManager() {
    L = luaL_newstate();
    luaL_openlibs(L);
    int err;
    err = luaL_dostring(L, FileSystem::read_file("main.lua").c_str());
    if(err == 1) throw "Error loading main.lua:\n" + std::string(lua_tostring(L, -1));
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

void LuaManager::update() {
    this->execute("__luma_system:process_update()");
    this->execute("__luma_system:process_draw()");
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
void LuaManager::pass_object_database_into_state(ObjectDatabase* objdatabase) {
    L->object_database = objdatabase;
}
