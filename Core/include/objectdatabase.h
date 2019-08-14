#pragma once
#include <objectasset.h>
#include <vector>
#include <filesystem.h>
#include <map>

class ObjectDatabase
{
public:
    ObjectDatabase();
    std::string get_object_code(size_t id);
    std::string get_object_name(size_t id);
    std::string get_object_default_sprite(size_t id);
    size_t      get_object_id(std::string str);

    std::vector<ObjectAsset*> get_all_object_assets();

    bool object_id_exists(size_t id);
    bool object_name_exists(std::string name);


private:
    std::vector<ObjectAsset*> object_assets;
    std::map<std::string, size_t> object_name_id_map;
};
