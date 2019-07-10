#pragma once
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#include <filesystem.h>

typedef int (*lua_CFunction) (lua_State *L);

class LuaManager
{
public:
    LuaManager();
    void execute(std::string str);
    int get_global_int(std::string name);
    void update();
    int register_function(lua_CFunction fnc, std::string name);
private:
    lua_State* L;
};
