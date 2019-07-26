#include "include/roommanager.h"
#include <filesystem.h>

RoomManager::RoomManager() : room_database(&background_database, &tileset_database) {
  default_room_id = room_database.get_id_from_name(FileSystem::get_default_room_name());
  current_room = room_database.get_asset(default_room_id);
}

void RoomManager::set_room(unsigned int id) {
  current_room = room_database.get_asset(id);
}

unsigned int RoomManager::get_current_room_id() {
  return current_room->get_id();
}

RoomAsset* RoomManager::get_current_room() {
  return current_room;
}

void RoomManager::draw_tiles(WindowManager* win_manager) {
  for(RoomTileLayer layer : current_room->get_tile_layers()) {
      for(RoomTile tile : layer.tiles) {
        SDL_Rect source = { tile.texture_x, tile.texture_y, tile.width, tile.height };
        SDL_Rect dest = { tile.x, tile.y, tile.width, tile.height };
        win_manager->draw(tileset_database.get_asset(tile.tileset_ref)->get_texture(), source, dest);
      }
  }
}

void RoomManager::draw_backgrounds(WindowManager* win_manager) {
  for(RoomBackground background : current_room->get_backgrounds()) {
      TextureAsset* tex = background_database.get_asset(background.asset_ref)->get_texture_asset();
      SDL_Rect source = { 0, 0, static_cast<int>(tex->get_size().x), static_cast<int>(tex->get_size().y) };
      win_manager->draw(tex, source, source);
  }
}

RoomDatabase* RoomManager::get_room_database() {
  return &room_database;
}
