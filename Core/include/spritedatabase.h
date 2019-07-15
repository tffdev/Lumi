#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <spriteasset.h>
#include <filesystem.h>

class SpriteDatabase
{
public:
    SpriteDatabase();
    sf::Sprite get_sprite_by_id(unsigned long long id, int subimage = 0);
    int get_sprite_id(std::string name);
    bool sprite_exists(std::string name);
private:
    std::vector<SpriteAsset> sprites;
    std::map<std::string, int> id_map;
    TextureManager texture_manager;
};
