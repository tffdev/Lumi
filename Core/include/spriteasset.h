#pragma once
#include <hitboxasset.h>
#include <vector>
#include <textureasset.h>
#include <subimagerect.h>
#include <mathlibrary.h>
#include <SDL2/SDL.h>

/**
 * SpriteAsset is referrable by a single ID and contains
 * many subimages (used for displaying animations) which share
 * common traits such as size, hitbox data and source texture.
 */
class SpriteAsset
{
public:
    SpriteAsset(std::string& name, std::string path, std::vector<SubimageRect*> rects, HitboxAsset hitbox);
    ~SpriteAsset();
    Vector2<int> get_subimage_size();
    SubimageRect* get_subimage(double subimage);
    std::string get_name();
    GLuint get_texture_id();
    Vector2<unsigned int> get_texture_size();
private:
    std::vector<SubimageRect*> subimages;
    TextureAsset texture;
    HitboxAsset hitbox;
    std::string name;
    Vector2<int> size;
};
