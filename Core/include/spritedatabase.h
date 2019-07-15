#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <spriteasset.h>

class SpriteDatabase
{
public:
    SpriteDatabase();
    sf::Sprite get_sprite_by_id(int id, int subimage = 0);
private:
    std::vector<SpriteAsset> sprites;
};
