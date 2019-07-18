#include "filesystem.h"

bool FileSystem::file_exists(std::string filename) {
  if (FILE * file = fopen((DATA_PATH + filename).c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

std::string FileSystem::read_file(std::string filename, bool binary) {
  if (!file_exists(DATA_PATH + filename)) throw "File " + filename + " doesn't exist!";
  std::ifstream stream(DATA_PATH + filename, (binary) ? std::ifstream::binary : std::ifstream:: in );
  std::string str((std::istreambuf_iterator < char > (stream)),
    std::istreambuf_iterator < char > ());
  return str;
}

std::string FileSystem::load_object_file() {
  if (!file_exists(OBJECT_PATH)) throw "Cannot load Object XML file.";
  return read_file(OBJECT_PATH);
}

std::string FileSystem::load_sprite_file() {
  if (!file_exists(SPRITE_PATH)) throw "Cannot load Sprite XML file.";
  return read_file(SPRITE_PATH);
}

std::string FileSystem::load_config_file() {
  if (!file_exists(CONFIG_PATH)) throw "Cannot load Config XML file.";
  return read_file(CONFIG_PATH);
}

std::vector<ObjectAsset*> FileSystem::load_objects() {
  pugi::xml_document document;
  std::vector<ObjectAsset*> object_vector;
  document.load_string(FileSystem::load_object_file().c_str());

  int i = 0;
  for (pugi::xml_node obj_xml: document.child("objects").children("object")) {
    object_vector.push_back(new ObjectAsset(i,
      obj_xml.child("name").text().as_string(),
      obj_xml.child("sprite").text().as_string(),
      obj_xml.child("code").text().as_string()));
    i++;
  }
  return object_vector;
}

std::vector<SpriteAsset> FileSystem::load_sprites(TextureManager& texture_manager) {
  pugi::xml_document document;
  std::vector<SpriteAsset> sprite_vector;
  document.load_string(FileSystem::load_sprite_file().c_str());

  int i = 0;
  for (pugi::xml_node spr_xml: document.child("sprites").children("sprite")) {
    // name assignment
    std::string name(spr_xml.child("name").text().as_string());

    // hitbox generation
    HitboxAsset hitbox(spr_xml.child("hitbox").child("shape").text().as_int(),
      spr_xml.child("hitbox").child("offset").child("x").text().as_int(),
      spr_xml.child("hitbox").child("offset").child("y").text().as_int(),
      spr_xml.child("hitbox").child("size").child("x").text().as_int(),
      spr_xml.child("hitbox").child("size").child("y").text().as_int());

    // rect generation
    std::vector<SubimageRect*> rects;
    for (pugi::xml_node subimage: spr_xml.child("subimages").children("subimage")) {
      SubimageRect* rect = new SubimageRect(
        subimage.child("x").text().as_int(),
        subimage.child("y").text().as_int(),
        subimage.child("width").text().as_int(),
        subimage.child("height").text().as_int());
      rects.push_back(rect);
    }


    // texture creation and population of texture_manager
    std::string texture_path = spr_xml.child("path").text().as_string();
    if (!texture_manager.has_texture(texture_path)) {
      texture_manager.insert(texture_path);
    }


    SpriteAsset spr(name, texture_manager.get_texture(texture_path), rects, hitbox);
    sprite_vector.push_back(spr);
    i++;
  }
  return sprite_vector;
}

unsigned int FileSystem::hex_string_to_uint(std::string str) {
  unsigned int x;
  std::stringstream ss;
  ss << std::hex << str;
  ss >> x;
  return static_cast<unsigned int>(x);
}

ConfigManager FileSystem::load_config() {
  pugi::xml_document document;
  document.load_string(FileSystem::load_config_file().c_str());

  ConfigManager config_asset(
    document.child("window").child("windowtitle").text().as_string(),
    document.child("window").child("windowsize").child("width").text().as_uint(),
    document.child("window").child("windowsize").child("height").text().as_uint(),
    hex_string_to_uint(std::string(document.child("window").child("windowdrawcolor").text().as_string()) + "ff"),
    document.child("window").child("scale").text().as_double());

  return config_asset;
}
