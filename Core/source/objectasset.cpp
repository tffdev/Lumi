#include "include/objectasset.h"

ObjectAsset::ObjectAsset(std::string name, std::string default_sprite)
    : name(name), default_sprite(default_sprite) {}

bool ObjectAsset::has_default_sprite() {
    return default_sprite.compare("") != 0;
}

std::string ObjectAsset::get_name() {
    return name;
}

std::string ObjectAsset::get_default_sprite() {
    return default_sprite;
}
