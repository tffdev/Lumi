#pragma once
#include <SFML/Graphics.hpp>
#include <configmanager.h>

class WindowManager
{
public:
    WindowManager(ConfigManager* config_manager, bool shown = true);

    void create_window_using_config();

    void clear();
    void draw(const sf::Drawable&);
    void display();
    bool poll_events(sf::Event&);
    bool is_open();
    void close();
    sf::Vector2u get_size();

    bool is_fullscreen();
    void set_fullscreen(bool);
    void toggle_fullscreen();
private:
    ConfigManager config;
    bool shown;
    sf::RenderWindow window;
    sf::Color clear_color;
    sf::View view;
};
