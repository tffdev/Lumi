#pragma once
#include <string>

class ObjectAsset
{
public:
    ObjectAsset(std::string name, std::string default_sprite = "", std::string code = "");
    std::string get_name();
    std::string get_default_sprite();
    std::string get_code();
    bool get_persistence();
    bool has_default_sprite();
    bool has_code();
private:
    std::string name;
    std::string default_sprite;
    std::string code;
    bool persistent;
};

