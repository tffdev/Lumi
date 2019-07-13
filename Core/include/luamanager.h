#pragma once
#include <lua.hpp>
#include <filesystem.h>
#include <objectdatabase.h>
#include <windowmanager.h>


class LuaManager
{
public:
    LuaManager();

    void run_update_function();
    void run_draw_function();

    lua_State* get_lua_state();

    void execute(std::string str);
    int get_global_int(std::string name);
    int register_function(lua_CFunction fnc, std::string name);
    int register_luma_system_function(lua_CFunction func, std::string name);
    void assign_state_containers(ObjectDatabase*, WindowManager*);
    void load_library(ObjectDatabase*, WindowManager*);

    int get_instance_count();
    int object_code_length();
private:
    lua_State* L;
};
