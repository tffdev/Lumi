#pragma once
#include <lua.hpp>
#include <filesystem.h>
#include <objectdatabase.h>

struct lua_state_extension {
    ObjectDatabase* object_database;
};

typedef struct lua_State : lua_state_extension {} lua_State;

class LuaManager
{
public:
    LuaManager();
    void update();
    void execute(std::string str);
    int get_global_int(std::string name);
    int register_function(lua_CFunction fnc, std::string name);
    int register_luma_system_function(lua_CFunction func, std::string name);
    void pass_object_database_into_state(ObjectDatabase* obj_database);
private:
    lua_State* L;
};
