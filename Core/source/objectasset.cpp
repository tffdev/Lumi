#include "include/objectasset.h"

ObjectAsset::ObjectAsset(int id, std::string name, std::string default_sprite, std::string code)
    : id(id),
      name(name),
      default_sprite(default_sprite),
      code(code)
{}

bool ObjectAsset::has_default_sprite() {
    return default_sprite.compare("") != 0;
}

bool ObjectAsset::has_code() {
    return code.compare("") != 0;
}

std::string ObjectAsset::get_name() {
    return name;
}

int ObjectAsset::get_id() {
    return id;
}

std::string ObjectAsset::get_default_sprite() {
    return default_sprite;
}

std::string ObjectAsset::get_code() {
    return code;
}
