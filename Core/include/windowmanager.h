#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_opengl.h>
#include <configmanager.h>
#include <spriteasset.h>
#include <GL/gl.h>
#include <GL/wglext.h>

class WindowManager
{
public:
    WindowManager(ConfigManager* config_manager);
    ~WindowManager();
    void create_window_using_config();

    void clear();
    void draw(SpriteAsset* sprite, double subimage, int x, int y);
    void draw(TextureAsset* sprite, SDL_Rect source, SDL_Rect dest);

    void display();
    bool poll_events(SDL_Event* e);
    bool is_open();
    void close();

    Vector2<unsigned int> get_size();
    Vector2<unsigned int> get_real_size();

    bool is_fullscreen();
    void set_fullscreen(bool);
    void toggle_fullscreen();
private:
    ConfigManager config;
    bool open = true;
    SDL_Window* window;
    SDL_GLContext context;
    Color clear_color;
    Vector2<unsigned int> size;

    Vector2<double> camera_position;
    double scale;
};
