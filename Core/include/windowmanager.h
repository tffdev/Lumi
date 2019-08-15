#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_opengl.h>
#include <spriteasset.h>
#include <GL/gl.h>
#include <GL/wglext.h>

static std::string DEBUG_ALPHABET = "!+#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

/**
 * @brief The Color class creates RGBA values given a unsigned int referring to a 32-bit color.
 */
class Color {
public:
  Color(unsigned int color_hex = 0) {
    r = (color_hex >> 16) % 0x100;
    g = (color_hex >> 8) % 0x100;
    b = (color_hex >> 0) % 0x100;
  }
  int r,g,b;
};

struct WindowConfiguration {
  std::string windowtitle;
  Vector2<unsigned int> size;
  double scale;
  Color clear_color;
  Uint32 fps;
};

class WindowManager
{
public:
    WindowManager();
    ~WindowManager();

    void clear();
    void draw(SpriteAsset* sprite, double subimage, double x, double y);
    void draw(TextureAsset* sprite, SDL_Rect source, SDL_Rect dest);
    void set_camera_position(double x, double y);

    void display();
    bool poll_events(SDL_Event* e);
    bool is_open();
    void close();

    Vector2<unsigned int> get_size();
    Vector2<unsigned int> get_real_size();

    bool is_fullscreen();
    void set_fullscreen(bool);
    void toggle_fullscreen();
    void bluescreen(std::string title, std::string error);

    void set_clear_color(Color new_color);

private:
    bool open = true;
    SDL_Window* window;
    SDL_GLContext context;
    Color clear_color;
    Vector2<unsigned int> size;

    Vector2<double> camera_position;
    double scale;

    bool fullscreen = false;

    bool bluescreened = false;
};
