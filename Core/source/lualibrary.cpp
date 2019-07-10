#include "lualibrary.h"

// __luma_system:get_object_id("objTest") --> 1
int luma_system_get_object_id(lua_State* L) {
    std::string name(lua_tostring(L, -1));
    if(L->object_database == nullptr) throw "aaa";
    if(L->object_database == nullptr || !L->object_database->object_name_exists(name)) {
        lua_pushnumber(L, 0);
        return 1;
    }
    int id = L->object_database->get_id_from_name(name);
    lua_pushnumber(L, id);
    return 1;
}

void LuaLibrary::load_library_into_manager(LuaManager* lmanager, ObjectDatabase* object_database) {
    lmanager->pass_object_database_into_state(object_database);
    lmanager->register_luma_system_function(luma_system_get_object_id, "get_object_id");
}
