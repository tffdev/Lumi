#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <configmanager.h>
#include <spriteasset.h>
#include <GL/gl.h>
#include <GL/wglext.h>

struct Color {
  float r;
  float g;
  float b;
  float a;
};

class WindowManager
{
public:
    WindowManager(ConfigManager* config_manager);
    ~WindowManager();
    void create_window_using_config();

    void clear();
    void draw(SpriteAsset* sprite, double subimage, int x, int y);
    void display();
    bool poll_events(SDL_Event* e);
    bool is_open();
    void close();
    Vector2<int> get_size();

    bool is_fullscreen();
    void set_fullscreen(bool);
    void toggle_fullscreen();
private:
    ConfigManager config;
    bool open = true;
    SDL_Window* window;
    SDL_GLContext context;
    Color clear_color;
};
