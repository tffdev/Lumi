#pragma once
#include <SDL2/SDL.h>
#include <mathlibrary.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <string>

class TextureAsset
{
public:
    TextureAsset(std::string path);
    ~TextureAsset();
    void destroy();
    GLuint get_texture_id();
    Vector2<unsigned int> get_size();
private:
    GLuint texture_id = 0;
    std::string path;
    bool loaded = false;
    Vector2<unsigned int> size;
};
