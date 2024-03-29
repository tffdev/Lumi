#include "filesystem.h"

pugi::xml_document& FileSystem::get_game_xml_file() {
  if(doc.child("project").empty())
    doc.load_string(FileSystem::read_file(game_file_name).c_str());

  return doc;
}


/**
 * @brief Check if a file exists within the virutal filesystem given a filepath.
 * @param filename The path of the file.
 * @return True if the file exists, false if not.
 */
bool FileSystem::file_exists(std::string filename) {
  if (FILE * file = fopen((data_path + filename).c_str(), "r")) {
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
  if (!file_exists(data_path + filename)) throw "File " + filename + " doesn't exist!";
  std::ifstream stream(data_path + filename, (binary) ? std::ifstream::binary : std::ifstream::in);
  std::string str((std::istreambuf_iterator<char>(stream)),
    std::istreambuf_iterator<char>());
  return str;
}

/**
 * @brief Using the default object xml file, create a vector of ObjectAssets.
 * @return A vector of ObjectAssets as per the objects.xml file.
 */
std::vector<ObjectAsset*> FileSystem::load_objects() {
  pugi::xml_node root = get_game_xml_file().child("project");

  std::vector<ObjectAsset*> object_vector;
  int i = 0;
  for (pugi::xml_node obj_xml: root.child("objects").children("object")) {
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
std::vector<SpriteAsset*> FileSystem::load_sprites() {
  std::vector<SpriteAsset*> sprite_vector;
  pugi::xml_node root = get_game_xml_file().child("project");

  int i = 0;
  for (pugi::xml_node spr_xml: root.child("sprites").children("sprite")) {
    // name assignment
    std::string name(spr_xml.attribute("name").as_string());

    // hitbox generation
    HitboxAsset hitbox(
      spr_xml.child("hitbox").attribute("shape").as_int(),
      spr_xml.child("hitbox").attribute("offset_x").as_int(),
      spr_xml.child("hitbox").attribute("offset_y").as_int(),
      spr_xml.child("hitbox").attribute("size_x").as_int(),
      spr_xml.child("hitbox").attribute("size_y").as_int());

    // rect generation
    std::vector<SubimageRect*> rects;
    for (pugi::xml_node subimage: spr_xml.child("subimages").children("subimage")) {
      SubimageRect* rect = new SubimageRect(
        subimage.attribute("x").as_int(),
        subimage.attribute("y").as_int(),
        subimage.attribute("width").as_int(),
        subimage.attribute("height").as_int());
      rects.push_back(rect);
    }


    // texture creation and population of texture_manager
    std::string texture_path = spr_xml.attribute("path").as_string();
    SpriteAsset* spr = new SpriteAsset(name, texture_path, rects, hitbox);
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
WindowConfiguration FileSystem::load_config() {
  pugi::xml_node root = get_game_xml_file().child("project");
  WindowConfiguration config;
  config.windowtitle = root.child("window").attribute("title").as_string();
  config.size.x = root.child("window").attribute("width").as_uint();
  config.size.y = root.child("window").attribute("height").as_uint();
  config.clear_color = Color(hex_string_to_uint(std::string(root.child("window").attribute("drawcolor").as_string())));
  config.scale = root.child("window").attribute("scale").as_double();

  return config;
}

/**
 * @brief Load a vector of AudioAssets referring to definitions in the sounds.xml file.
 * @return A vectof of AudioAsset pointers.
 */
std::vector<AudioAsset*> FileSystem::load_sounds() {
  pugi::xml_node root = get_game_xml_file().child("project");
  std::vector<AudioAsset*> audio_assets;
  unsigned long long i = 0;
  for(pugi::xml_node node : root.child("sounds").children("sound")) {
    audio_assets.push_back(new AudioAsset(i, node.attribute("name").as_string(), node.attribute("path").as_string()));
    i++;
  }

  return audio_assets;
}

std::vector<BackgroundAsset*> FileSystem::load_backgrounds() {
  pugi::xml_node root = get_game_xml_file().child("project");
  std::vector<BackgroundAsset*> backgrounds;
  unsigned long long i = 0;
  for(pugi::xml_node node : root.child("backgrounds").children("background")) {
    TextureAsset* texture = new TextureAsset(node.attribute("path").as_string());
    backgrounds.push_back(new BackgroundAsset(i, node.attribute("name").as_string(), texture));
    i++;
  }

  return backgrounds;
}

std::vector<TilesetAsset*> FileSystem::load_tilesets() {
  pugi::xml_node root = get_game_xml_file().child("project");
  std::vector<TilesetAsset*> tilesets;
  unsigned int i = 0;
  for(pugi::xml_node node : root.child("tilesets").children("tileset")) {
    tilesets.push_back(new TilesetAsset(i, node.attribute("name").as_string(), node.attribute("path").as_string()));
    i++;
  }

  return tilesets;
}

std::vector<RoomAsset*>
FileSystem::load_rooms(TilesetDatabase* tileset_db, BackgroundDatabase* background_db)
{
  pugi::xml_node root = get_game_xml_file().child("project");

  std::vector<RoomAsset*> room_assets;
  unsigned int i = 0;
  for(pugi::xml_node node : root.child("rooms").children("room")) {

    // build tile layers
    std::vector<RoomTileLayer> room_tile_layers;
    for(pugi::xml_node tile_layer : node.child("tile_layers").children("layer")) {
      RoomTileLayer layer;
      for(pugi::xml_node xml_tile : tile_layer.children("tile")) {
          RoomTile tile;
          tile.x = xml_tile.attribute("x").as_int();
          tile.y = xml_tile.attribute("y").as_int();
          tile.width = xml_tile.attribute("width").as_int();
          tile.height = xml_tile.attribute("height").as_int();
          tile.texture_x = xml_tile.attribute("texture_x").as_int();
          tile.texture_y = xml_tile.attribute("texture_y").as_int();
          tile.tileset_ref = tileset_db->get_id_from_name(xml_tile.attribute("tileset").as_string());
          layer.tiles.push_back(tile);
      }
      room_tile_layers.push_back(layer);
    }

    // build backgrounds
    std::vector<RoomBackground> room_backgrounds;
    for(pugi::xml_node bg_node : node.child("backgrounds").children("background")) {
      RoomBackground rm_bg;
      rm_bg.depth = bg_node.attribute("depth").as_int();
      rm_bg.offset_x = bg_node.attribute("offset_x").as_int();
      rm_bg.offset_y = bg_node.attribute("offset_y").as_int();
      rm_bg.asset_ref = background_db->get_id(bg_node.attribute("image").as_string());
      room_backgrounds.push_back(rm_bg);
    }

    // instance placements
    std::vector<InstancePlacement> room_instance_placements;
    for(pugi::xml_node instance_node : node.child("instances").children("instance")) {
      InstancePlacement instance;
      instance.object_name = instance_node.attribute("name").as_string();
      instance.position = { instance_node.attribute("x").as_int(), instance_node.attribute("y").as_int() };
      room_instance_placements.push_back(instance);
    }

    room_assets.push_back(
          new RoomAsset(i,
                        node.attribute("name").as_string(),
                        node.child("creationcode").text().as_string(),
                        node.attribute("width").as_uint(),
                        node.attribute("height").as_uint(),
                        room_tile_layers,
                        room_backgrounds,
                        room_instance_placements));

    i++;
  }

  return room_assets;
}

std::string FileSystem::get_default_room_name() {
  return get_game_xml_file().child("project").child("window").attribute("defaultroom").as_string();
}

void FileSystem::set_data_path(std::string path) {
  data_path = path;
}

void FileSystem::set_game_file_name(std::string path) {
  game_file_name = path;
}
