#pragma once
#include <SFML/Graphics.hpp>
#include <hitboxasset.h>
#include <vector>
#include <textureasset.h>
#include <subimagerect.h>
#include <mathlibrary.h>

/**
 * SpriteAsset is referrable by a single ID and contains
 * many subimages (used for displaying animations) which share
 * common traits such as size, hitbox data and source texture.
 */
class SpriteAsset
{
public:
    SpriteAsset(std::string& name, TextureAsset& texture, std::vector<SubimageRect*> rects, HitboxAsset hitbox);
    Vector2<int> get_subimage_size();
    sf::Sprite get_subimage(double subimage);
    std::string get_name();
private:
    int textureid;
    TextureAsset& texture;
    HitboxAsset hitbox;
    std::string name;
    Vector2<int> size;
    std::vector<sf::Sprite> subimages;
};
