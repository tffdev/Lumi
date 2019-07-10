#include "include/objectdatabase.h"

ObjectDatabase::ObjectDatabase() {
    objects = FileSystem::load_objects();
    for(ObjectAsset* obj : objects)
        object_name_map.insert(std::pair<std::string, int>(obj->get_name(), obj->get_id()));
}

std::string ObjectDatabase::get_object_name(int id) {
    try {
        return objects.at(static_cast<unsigned long long>(id))->get_name();
    } catch (...) {
        return "";
    }
}

int ObjectDatabase::get_id_from_name(std::string name) {
    try {
         return object_name_map.at(name);
    } catch (...) {
        return -1;
    }
}

std::string ObjectDatabase::get_object_code(int id) {
    try {
        return objects.at(static_cast<unsigned long long>(id))->get_code();
    } catch (...) {
        return "";
    }
}

bool ObjectDatabase::object_name_exists(std::string name) {
    try {
         return (object_name_map.at(name)) ? true : false;
    } catch (...) {
        return false;
    }
}

bool ObjectDatabase::object_id_exists(int id) {
    try {
         return (objects.at(static_cast<unsigned long long>(id))) ? true : false;
    } catch (...) {
        return false;
    }
}
