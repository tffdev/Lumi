#include "include/objectdatabase.h"

ObjectDatabase::ObjectDatabase() {
    object_assets = FileSystem::load_objects();
    for(ObjectAsset* obj : object_assets){
        object_name_id_map.insert(std::pair<std::string, int>(obj->get_name(), obj->get_id()));
    }
}

std::string ObjectDatabase::get_object_name(int id) {
    try {
        return object_assets.at(static_cast<unsigned long long>(id))->get_name();
    } catch (...) {
        return "";
    }
}

int ObjectDatabase::get_object_id(std::string name) {
    try {
         return object_name_id_map.at(name);
    } catch (...) {
        return -1;
    }
}

std::string ObjectDatabase::get_object_code(int id) {
    try {
        return object_assets.at(static_cast<unsigned long long>(id))->get_code();
    } catch (...) {
        return "";
    }
}

bool ObjectDatabase::object_name_exists(std::string name) {
   return (object_name_id_map.count(name) == 0) ? false : true;
}

bool ObjectDatabase::object_id_exists(int id) {
    try {
         return (object_assets.at(static_cast<unsigned long long>(id))) ? true : false;
    } catch (...) {
        return false;
    }
}

std::vector<ObjectAsset*> ObjectDatabase::get_all_object_assets() {
    return object_assets;
}
