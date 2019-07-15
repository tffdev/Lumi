#pragma once
#include <SFML/Graphics.hpp>
#include <hitboxasset.h>
#include <vector>
#include <textureasset.h>
#include <subimagerect.h>

/**
 * SpriteAsset is referrable by a single ID and contains
 * many subimages (used for displaying animations) which share
 * common traits such as size, hitbox data and source texture.
 */
class SpriteAsset
{
public:
    SpriteAsset(TextureAsset& texture, std::vector<SubimageRect*> rects, HitboxAsset hitbox);
    sf::Vector2i get_subimage_size();
    sf::Sprite get_sprite(double subimage);
private:
    int textureid;
    TextureAsset& texture;
    sf::Vector2i size;
    std::vector<sf::Sprite> subimages;
    HitboxAsset hitbox;
};
