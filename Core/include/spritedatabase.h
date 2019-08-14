#pragma once
#include <vector>
#include <spriteasset.h>
#include <filesystem.h>

class SpriteDatabase
{
public:
    SpriteDatabase();
    ~SpriteDatabase();
    SpriteAsset* get_sprite_by_id(size_t id);
    size_t get_sprite_id(std::string name);
    bool sprite_exists(std::string name);
private:
    std::vector<SpriteAsset*> sprites;
    std::map<std::string, size_t> id_map;
};
