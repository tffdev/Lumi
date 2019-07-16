#pragma once
#include <SFML/Graphics.hpp>
#include <mathlibrary.h>

class HitboxAsset
{
public:
    HitboxAsset(int shape, int offsetx, int offsety, int sizex, int sizey);
    Vector2<int> get_size();
    Vector2<int> get_offset();
private:
    int shape;
    Vector2<int> offset;
    Vector2<int> size;
};
