#pragma once
#include <lua.hpp>
#include <filesystem.h>
#include <objectdatabase.h>


/**
 * @brief The lua_state_extension struct extends the current
 * Lua state to also contain pointers to components in our running game.
 * This lets us access game-state data within the Lua box such as drawing utilities.
 */
struct lua_state_extension {
    ObjectDatabase* object_database;
};

typedef struct lua_State : lua_state_extension {} lua_State;



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
    void pass_object_database_into_state(ObjectDatabase* obj_database);
    void load_object_instantiation_code(ObjectDatabase* obj_database);
private:
    lua_State* L;
};
