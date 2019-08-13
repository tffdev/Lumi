#pragma once
#include <lua.hpp>
#include <filesystem.h>
#include <objectdatabase.h>
#include <windowmanager.h>
#include <spritedatabase.h>
#include <inputmanager.h>
#include <audiodatabase.h>
#include <roommanager.h>

class LuaManager
{
public:
    LuaManager();

    void run_update_function();
    void run_draw_function();

    lua_State* get_lua_state();

    void execute(std::string str);
    int get_global_int(std::string name);
    double get_global_double(std::string name);
    int register_function(lua_CFunction fnc, std::string name);
    int register_lumi_system_function(lua_CFunction func, std::string name);
    void assign_state_containers(ObjectDatabase*, WindowManager*, SpriteDatabase*, InputManager*, AudioDatabase*, RoomManager*);
    void load_library(ObjectDatabase*, WindowManager*, SpriteDatabase*, InputManager*, AudioDatabase*, RoomManager*);

    int get_instance_count();
    int object_code_length();
    void load_object_code(ObjectDatabase* database);
private:
    lua_State* L;
};
