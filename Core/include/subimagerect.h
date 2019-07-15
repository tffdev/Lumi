#pragma once
#include <SFML/Graphics.hpp>

class SubimageRect
{
public:
    SubimageRect(int x, int y, int width, int height);
    sf::IntRect get_rect();
private:
    sf::IntRect rect;
};
