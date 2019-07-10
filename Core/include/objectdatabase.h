#pragma once
#include <objectasset.h>
#include <vector>
#include <filesystem.h>

class ObjectDatabase
{
public:
    ObjectDatabase();
    std::string get_object_code(int id);
    std::string get_object_name(int id);
    std::string get_object_default_sprite(int id);
    bool object_id_exists(int id);
    bool object_name_exists(std::string name);
    int get_id_from_name(std::string str);
private:
    std::vector<ObjectAsset*> objects;
    std::map<std::string, int> object_name_map;
};
