#pragma once
#include <luamanager.h>

namespace LuaLibrary {
    void load_library_into_manager(LuaManager* lmanager, ObjectDatabase* object_database);
};
