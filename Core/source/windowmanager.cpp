#include "windowmanager.h"

WindowManager::WindowManager(ConfigManager* config_manager, bool shown)
    : config(*config_manager),
      shown(shown) {
    create_window_using_config();
}

void WindowManager::create_window_using_config() {
    sf::VideoMode mode(config.get_window_size().x,
                       config.get_window_size().y);

    auto style = sf::Style::Default;
    if(config.get_fullscreen()) style = sf::Style::Fullscreen;
    if(!shown) style = sf::Style::None;

    window.create(mode, config.get_window_title(), style);

    window.setVisible(shown);
    //window.setFramerateLimit(60);
}

bool WindowManager::is_open() {
    return window.isOpen();
}

void WindowManager::close() {
    window.close();
}

void WindowManager::clear() {
    window.clear(clear_color);
}

void WindowManager::draw(const sf::Drawable& spr) {
    window.draw(spr);
}

void WindowManager::display() {
    window.display();
}

bool WindowManager::poll_events(sf::Event& e) {
    return window.pollEvent(e);
}

sf::Vector2u WindowManager::get_size() {
    return window.getSize();
}

void WindowManager::toggle_fullscreen() {
    config.set_fullscreen(!config.get_fullscreen());
    create_window_using_config();
}

void WindowManager::set_fullscreen(bool set) {
    config.set_fullscreen(set);
    create_window_using_config();
}
