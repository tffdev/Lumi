#include "projectdata.h"

bool ProjectData::asset_name_exists(std::string name) {
  return rooms.asset_exists(name) ||
         sounds.asset_exists(name) ||
         objects.asset_exists(name) ||
         sprites.asset_exists(name) ||
         tilesets.asset_exists(name) ||
         backgrounds.asset_exists(name);
}

void ProjectData::clear_all_databases() {
  // clear databases
  objects.clear();
  rooms.clear();
  sounds.clear();
  sprites.clear();
  backgrounds.clear();
  tilesets.clear();
}

void ProjectData::load_rooms_from_xml(pugi::xml_node& root) {
  // load rooms
  for(pugi::xml_node node : root.child("rooms").children()) {
    RoomAsset asset;
    asset.name = node.attribute("name").as_string();
    asset.size.x = node.attribute("width").as_int();
    asset.size.y = node.attribute("height").as_int();
    asset.creation_code = node.child("creationcode").text().as_string();
    // push room instances
    for(pugi::xml_node instance : node.child("instances").children()) {
      RoomInstance rminst;
      rminst.name = instance.attribute("name").as_string();
      rminst.position = {
        instance.attribute("x").as_int(),
        instance.attribute("y").as_int()
      };
      asset.instances.push_back(rminst);
    }

    // push tile layers
    for(pugi::xml_node layer_node : node.child("tile_layers").children()) {
      TileLayer layer;
      layer.name = layer_node.attribute("name").as_string();
      layer.depth = layer_node.attribute("depth").as_int();
      std::vector<Tile> tiles;

      // push individual tiles per layer
      for(pugi::xml_node layer_tile_node : layer_node.children()) {
        Tile tile;
        tile.position = {layer_tile_node.attribute("x").as_int(), layer_tile_node.attribute("y").as_int()};
        tile.size = {layer_tile_node.attribute("width").as_int(), layer_tile_node.attribute("height").as_int()};
        tile.texture_position = {layer_tile_node.attribute("texture_x").as_int(), layer_tile_node.attribute("texture_y").as_int()};
        tile.tileset_name = layer_tile_node.attribute("tileset").as_string();
        tiles.push_back(tile);
      }

      layer.tiles = tiles;
      asset.tile_layers.push_back(layer);
    }

    // push backgrounds
    for(pugi::xml_node bg_node : node.child("backgrounds").children()) {
      RoomBackground bg;
      bg.image = bg_node.attribute("image").as_string();
      bg.depth = bg_node.attribute("depth").as_int();
      bg.offset = {
        bg_node.attribute("offset_x").as_int(),
        bg_node.attribute("offset_y").as_int()
      };
    }
    // push created asset into database
    rooms.insert_asset(asset.name, asset);
  }
}

void ProjectData::load_sounds_from_xml(pugi::xml_node &root) {
  for(pugi::xml_node sound_node : root.child("sounds").children()) {
    SoundAsset sound;
    sound.name = sound_node.attribute("name").as_string();
    sound.path = sound_node.attribute("path").as_string();
    sounds.insert_asset(sound.name, sound);
  }
}

void ProjectData::load_objects_from_xml(pugi::xml_node& root) {
  // load objects
  for(pugi::xml_node node : root.child("objects").children()) {
      ObjectAsset asset;
      asset.name = node.attribute("name").as_string();
      asset.sprite_name = node.attribute("sprite").as_string();
      asset.persistent = node.attribute("persistent").as_bool();
      asset.code = node.text().as_string();
      objects.insert_asset(asset.name, asset);
  }
}

void ProjectData::load_sprites_from_xml(pugi::xml_node &root) {
  for(pugi::xml_node node : root.child("sprites").children()){
    SpriteAsset sprite;
    sprite.name = node.attribute("name").as_string();
    sprite.size = {
      node.attribute("width").as_int(),
      node.attribute("height").as_int()
    };
    sprite.origin = {
      node.attribute("origin_x").as_int(),
      node.attribute("origin_y").as_int()
    };
    sprite.texture_path = node.attribute("path").as_string();

    // assign hitbox to sprite
    HitboxAsset hitbox;
    hitbox.shape = node.child("hitbox").attribute("shape").as_uint();
    hitbox.size = {
      node.child("hitbox").attribute("size_x").as_int(),
      node.child("hitbox").attribute("size_y").as_int()
    };
    hitbox.offset = {
      node.child("hitbox").attribute("offset_x").as_int(),
      node.child("hitbox").attribute("offset_y").as_int()
    };
    sprite.hitbox = hitbox;

    // push subimages into sprite
    std::vector<Subimage> subimages;
    for(pugi::xml_node subimage_node : node.child("subimages").children()) {
      Subimage subimg;
      subimg.texture_pos = {
        subimage_node.attribute("x").as_int(),
        subimage_node.attribute("y").as_int()
      };
      subimg.size = {
        subimage_node.attribute("width").as_int(),
        subimage_node.attribute("height").as_int()
      };
    }
    sprite.subimages = subimages;

    // push into database
    sprites.insert_asset(sprite.name, sprite);
  }
}

void ProjectData::load_tilesets_from_xml(pugi::xml_node &root) {
  for(pugi::xml_node node : root.child("tilesets").children()){
    TilesetAsset asset;
    asset.name = node.attribute("name").as_string();
    asset.tile_size = {
      node.attribute("size_x").as_int(),
      node.attribute("size_y").as_int()
    };
    asset.texture_path = node.attribute("path").as_string();
    tilesets.insert_asset(asset.name, asset);
  }
}

void ProjectData::load_backgrounds_from_xml(pugi::xml_node &root) {
  for(pugi::xml_node node : root.child("backgrounds").children()){
    BackgroundAsset asset;
    asset.name = node.attribute("name").as_string();
    asset.path = node.attribute("path").as_string();
    backgrounds.insert_asset(asset.name, asset);
  }
}

void ProjectData::load_config_from_xml(pugi::xml_node &root) {
  pugi::xml_node window_node = root.child("window");
  config.size = { window_node.attribute("width").as_int(),
                  window_node.attribute("height").as_int() };
  config.fps = window_node.attribute("fps").as_uint();
  config.scale = window_node.attribute("scale").as_double();
  config.title = window_node.attribute("title").as_string();
  config.background_color = std::strtoul(window_node.attribute("drawcolor").as_string(), nullptr, 16);
}

bool ProjectData::load_project_file_into_databases(std::string path) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(path.c_str());
  if (result) {
    printf("Parsed project %s without errors!\n", path.c_str());
  }else{
    printf("Error: %s at %lld", result.description(), result.offset);
    return false;
  }

  clear_all_databases();

  pugi::xml_node root = doc.child("project");

  // load project name
  game_name = root.child("name").text().as_string();

  // Load project into databases
  load_objects_from_xml(root);
  load_rooms_from_xml(root);
  load_sounds_from_xml(root);
  load_sprites_from_xml(root);
  load_tilesets_from_xml(root);
  load_backgrounds_from_xml(root);
  load_config_from_xml(root);

  return true;
}

// getters
Database<ObjectAsset>& ProjectData::get_objects() {
  return objects;
}
Database<RoomAsset>& ProjectData::get_rooms() {
  return rooms;
}
Database<SoundAsset>& ProjectData::get_sounds() {
  return sounds;
}
Database<SpriteAsset>& ProjectData::get_sprites() {
  return sprites;
}
Database<BackgroundAsset>& ProjectData::get_backgrounds() {
  return backgrounds;
}
Database<TilesetAsset>& ProjectData::get_tilesets() {
  return tilesets;
}
