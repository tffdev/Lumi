#pragma once
#include <objectasset.h>
#include <instanceasset.h>
#include <vector>
#include <filesystem.h>
#include <map>

class ObjectDatabase
{
public:
    ObjectDatabase();
    std::string get_object_code(int id);
    std::string get_object_name(int id);
    std::string get_object_default_sprite(int id);
    int         get_object_id(std::string str);

    void add_instance(InstanceAsset* instance);
    int instance_count();

    std::vector<ObjectAsset*> get_all_object_assets();
    std::vector<InstanceAsset*> get_all_instances();

    bool object_id_exists(int id);
    bool object_name_exists(std::string name);


private:
    std::vector<ObjectAsset*> object_assets;
    std::vector<InstanceAsset*> instances;
    std::map<std::string, int> object_name_id_map;
};
