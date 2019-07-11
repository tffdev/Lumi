#pragma once
#include <luamanager.h>

namespace LuaLibrary {
    void load_library(LuaManager* lmanager, ObjectDatabase* object_database);

    int push_environment_to_registry(lua_State* L);
    void fetch_environment_from_registry(lua_State* L, int index);
    void remove_environment_from_registry(lua_State* L, int index);

    int create_new_instance_environment(lua_State* L, int x, int y);
    void run_string_in_environment(lua_State* L, int index, std::string command);
};
