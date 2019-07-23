#pragma once
#include <vector>
#include <spriteasset.h>
#include <filesystem.h>

class SpriteDatabase
{
public:
    SpriteDatabase();
    ~SpriteDatabase();
    SpriteAsset* get_sprite_by_id(unsigned long long id);
    int get_sprite_id(std::string name);
    bool sprite_exists(std::string name);
private:
    std::vector<SpriteAsset*> sprites;
    std::map<std::string, int> id_map;
};
