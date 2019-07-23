#include "filesystem.h"

/**
 * @brief Check if a file exists within the virutal filesystem given a filepath.
 * @param filename The path of the file.
 * @return True if the file exists, false if not.
 */
bool FileSystem::file_exists(std::string filename) {
  if (FILE * file = fopen((DATA_PATH + filename).c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Read the contents of a file into a string.
 * @param filename The path of the file.
 * @param binary Whether the file is a binary asset or not.
 * @return The file's contents as a string.
 */
std::string FileSystem::read_file(std::string filename, bool binary) {
  if (!file_exists(DATA_PATH + filename)) throw "File " + filename + " doesn't exist!";
  std::ifstream stream(DATA_PATH + filename, (binary) ? std::ifstream::binary : std::ifstream:: in );
  std::string str((std::istreambuf_iterator < char > (stream)),
    std::istreambuf_iterator < char > ());
  return str;
}

/**
 * @brief Load the contents of the default object file as a string.
 * @return The default object file's contents as a string.
 */
std::string FileSystem::load_object_file() {
  if (!file_exists(OBJECT_PATH)) throw "Cannot load Object XML file.";
  return read_file(OBJECT_PATH);
}

/**
 * @brief Load the contents of the default sprite file as a string.
 * @return The default sprite file's contents as a string.
 */
std::string FileSystem::load_sprite_file() {
  if (!file_exists(SPRITE_PATH)) throw "Cannot load Sprite XML file.";
  return read_file(SPRITE_PATH);
}

/**
 * @brief Load the contents of the default config file as a string.
 * @return The default config file's contents as a string.
 */
std::string FileSystem::load_config_file() {
  if (!file_exists(CONFIG_PATH)) throw "Cannot load Config XML file.";
  return read_file(CONFIG_PATH);
}

/**
 * @brief Load the contents of the default config file as a string.
 * @return The default config file's contents as a string.
 */
std::string FileSystem::load_sounds_file() {
  if (!file_exists(AUDIO_PATH)) throw "Cannot load Sounds XML file.";
  return read_file(AUDIO_PATH);
}

/**
 * @brief Using the default object xml file, create a vector of ObjectAssets.
 * @return A vector of ObjectAssets as per the objects.xml file.
 */
std::vector<ObjectAsset*> FileSystem::load_objects() {
  pugi::xml_document document;
  std::vector<ObjectAsset*> object_vector;
  document.load_string(FileSystem::load_object_file().c_str());

  int i = 0;
  for (pugi::xml_node obj_xml: document.child("objects").children("object")) {
    object_vector.push_back(new ObjectAsset(i,
      obj_xml.attribute("name").as_string(),
      obj_xml.attribute("sprite").as_string(),
      obj_xml.text().as_string()));
    i++;
  }
  return object_vector;
}

/**
 * @brief Using the default sprite xml file, create a vector of SpriteAssets. Loads all required textures into the given TextureManager.
 * @param texture_manager The manager which to store all the required textures in.
 * @return A vector of SpriteAssets as per the sprites.xml file.
 */
std::vector<SpriteAsset> FileSystem::load_sprites(TextureDatabase& texture_database) {
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
    if (!texture_database.has_texture(texture_path)) {
      texture_database.insert(texture_path);
    }


    SpriteAsset spr(name, texture_database.get_texture(texture_path), rects, hitbox);
    sprite_vector.push_back(spr);
    i++;
  }
  return sprite_vector;
}

/**
 * @brief Convert a hexadecimal string to an unsigned int. Used for colors.
 * @param str The hexadecimal as a string.
 * @return The hexadecimal as a real integer value.
 */
unsigned int FileSystem::hex_string_to_uint(std::string str) {
  unsigned int x;
  std::stringstream ss;
  ss << std::hex << str;
  ss >> x;
  return static_cast<unsigned int>(x);
}

/**
 * @brief Create a ConfigManager object given the values within the default config.xml file.
 * @return An instance of ConfigManager.
 */
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

/**
 * @brief Load a vector of AudioAssets referring to definitions in the sounds.xml file.
 * @return A vectof of AudioAsset pointers.
 */
std::vector<AudioAsset*> FileSystem::load_sounds() {
  pugi::xml_document document;
  document.load_string(FileSystem::load_sounds_file().c_str());

  std::vector<AudioAsset*> audio_assets;
  unsigned long long i = 0;
  for(pugi::xml_node node : document.child("sounds").children("sound")) {
    audio_assets.push_back(new AudioAsset(i, node.child("name").text().as_string(), node.child("path").text().as_string()));
    i++;
  }

  return audio_assets;
}


std::vector<BackgroundAsset*> FileSystem::load_backgrounds() {
  pugi::xml_document document;
  document.load_string(FileSystem::read_file(BACKGROUND_PATH).c_str());

  std::vector<BackgroundAsset*> backgrounds;
  unsigned long long i = 0;
  for(pugi::xml_node node : document.child("backgrounds").children("background")) {
    TextureAsset texture(node.attribute("path").as_string());
    backgrounds.push_back(new BackgroundAsset(i, node.attribute("name").as_string(), texture));
    i++;
  }

  return backgrounds;
}
