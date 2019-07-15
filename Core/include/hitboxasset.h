#pragma once
#include <SFML/Graphics.hpp>

class HitboxAsset
{
public:
    HitboxAsset(int shape, int offsetx, int offsety, int sizex, int sizey);
    sf::Vector2i get_size();
    sf::Vector2i get_offset();
private:
    int shape;
    sf::Vector2i offset;
    sf::Vector2i size;
};
