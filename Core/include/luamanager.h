#pragma once
#define LUA_LIB
#include <lua.hpp>
#include <filesystem.h>

class LuaManager
{
public:
    LuaManager();
    void execute(std::string str);
    int get_global_int(std::string name);
private:
    lua_State* L;
};
