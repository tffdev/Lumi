#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <filesystem.h>
#include <objectasset.h>
#include <luamanager.h>
#include <configmanager.h>
#include <objectdatabase.h>
#include <lualibrary.h>
#include <windowmanager.h>
#include <textureasset.h>
#include <spritedatabase.h>
#include <inputmanager.h>

TEST_CASE("Sanity Check") {
  CHECK(1 == 1);
  SUBCASE("Nested Sanity Check") {
    CHECK(4 == 4);
  }
}

/**
 * ASSETS
 */
TEST_CASE("ObjectAsset") {
  ObjectAsset asset(1, "objTest", "sprTest", "x = 10");
  CHECK_EQ(asset.has_default_sprite(), true);
  CHECK_EQ(asset.has_code(), true);
  CHECK_EQ(asset.get_name().compare("objTest"), 0);
  CHECK_EQ(asset.get_default_sprite().compare("sprTest"), 0);
  CHECK_EQ(asset.get_code().compare("x = 10"), 0);

  ObjectAsset asset2(2, "objTest2");
  CHECK_EQ(asset2.has_default_sprite(), false);
  CHECK_EQ(asset2.has_code(), false);
  CHECK_EQ(asset2.get_name().compare("objTest2"), 0);
  CHECK_EQ(asset2.get_default_sprite().compare(""), 0);
  CHECK_EQ(asset2.get_code().compare(""), 0);
}

TEST_CASE("HitboxAsset") {
  HitboxAsset hitbox(0, 10, 15, 20, 25);
  CHECK_EQ(hitbox.get_size().x, 20);
  CHECK_EQ(hitbox.get_size().y, 25);
  CHECK_EQ(hitbox.get_offset().x, 10);
  CHECK_EQ(hitbox.get_offset().y, 15);
}

TEST_CASE("TextureAsset") {
  TextureAsset texture("images/playerRunSheet.png");
  CHECK_EQ(texture.get_size().x, 320);
  CHECK_EQ(texture.get_size().y, 80);
}

TEST_CASE("SubimageRect") {
  SubimageRect rect(10, 15, 40, 50);
  CHECK_EQ(rect.get_rect().left, 10);
  CHECK_EQ(rect.get_rect().top, 15);
  CHECK_EQ(rect.get_rect().width, 40);
  CHECK_EQ(rect.get_rect().height, 50);
}

TEST_CASE("SpriteAsset") {
  // this will be fetched from the database
  TextureAsset texture("images/playerRunSheet.png");

  // Assign hitbox to sprite
  HitboxAsset hitbox(0, 20, 0, 40, 80);

  // subimage rects
  std::vector<SubimageRect*> rects;
  rects.push_back(new SubimageRect(0, 0, 80, 80));
  rects.push_back(new SubimageRect(80, 0, 80, 80));
  rects.push_back(new SubimageRect(160, 0, 80, 80));
  rects.push_back(new SubimageRect(240, 0, 80, 80));

  std::string name("mySprite");
  SpriteAsset sprite(name, texture, rects, hitbox);

  CHECK_EQ(sprite.get_subimage_size().x, 80);
  CHECK_EQ(sprite.get_subimage_size().y, 80);
  CHECK_EQ(sprite.get_name().compare("mySprite"), 0);
}

/**
 * MANAGERS
 */
TEST_CASE("ConfigManager") {
  ConfigManager conf_manager("Hello", 320, 240, 0x32d61cff);
  CHECK_EQ(conf_manager.get_window_size().x, 320);
  CHECK_EQ(conf_manager.get_window_size().y, 240);
  CHECK_EQ(conf_manager.get_window_title().compare("Hello"), 0);
  CHECK_EQ(conf_manager.get_window_draw_color().r, 50);
  CHECK_EQ(conf_manager.get_window_draw_color().g, 214);
  CHECK_EQ(conf_manager.get_window_draw_color().b, 28);
  CHECK_EQ(conf_manager.get_window_draw_color().a, 255);
}

TEST_CASE("WindowManager") {
  ConfigManager config("hi", 320, 240, 0xff0000, 2.0);
  WindowManager window_manager(&config);
  CHECK_EQ(window_manager.is_open(), true);
  CHECK_EQ(window_manager.get_size().x, 320);
  CHECK_EQ(window_manager.get_size().y, 240);
  CHECK_EQ(window_manager.get_real_size().x, 640);
  CHECK_EQ(window_manager.get_real_size().y, 480);
  window_manager.close();
  CHECK_EQ(window_manager.is_open(), false);
}

TEST_CASE("TextureManager") {
  TextureManager texture_manager;

  std::string path = "images/playerRunSheet.png";
  CHECK_EQ(texture_manager.has_texture(path), false);

  texture_manager.insert(path);
  CHECK_EQ(texture_manager.has_texture(path), true);
  CHECK_EQ(texture_manager.get_textures_size(), 1);

  TextureAsset texture(path);
  CHECK_EQ(texture_manager.get_texture(path).get_size().x, texture.get_size().x);
  CHECK_EQ(texture_manager.get_texture(path).get_size().y, texture.get_size().y);

  texture_manager.destroy_all();
  CHECK_EQ(texture_manager.get_textures_size(), 0);
}

TEST_CASE("InputManager") {

}

int func_reg_check(lua_State *L) {
  lua_pushnumber(L, 68923);
  return 1;
}

TEST_CASE("LuaManager") {
  WindowManager window_manager(new ConfigManager("hi", 320, 240, 0xff0000ff));
  InputManager input_manager;
  ObjectDatabase obj_database;
  SpriteDatabase spr_database;
  LuaManager lmanager;
  lmanager.load_library(&obj_database, &window_manager, &spr_database, &input_manager);

  SUBCASE("Lua execution check") {
    lmanager.execute("___lua_execute_check = 370439");
    CHECK_EQ(lmanager.get_global_int("___lua_execute_check"), 370439);
    CHECK_EQ(lmanager.get_global_int("nonexistant_variable_check"), 0);
  }
  SUBCASE("Load main and objects check"){
    CHECK_EQ(lmanager.get_global_int("___lua_main_check"), 983652);
    CHECK_EQ(lmanager.get_global_int("objTest"), 0);
    CHECK_EQ(lmanager.get_global_int("objTest2"), 1);
    CHECK_EQ(lmanager.get_global_int("playerRun"), 0);
    CHECK_EQ(lmanager.get_global_int("sprCat"), 1);
  }
  SUBCASE("Invalid code throw check"){
    bool error = false;
    try { lmanager.execute("lk hsd dglg"); } catch (...) { error = true; }
    CHECK_EQ(error, true);
  }
  SUBCASE("Lua Function Registration") {
    lmanager.register_function(func_reg_check, "func_reg_check");
    lmanager.execute("func_reg_check_var = func_reg_check()");
    CHECK_EQ(lmanager.get_global_int("func_reg_check_var"), 68923);

    // Register function to __luma_system table.
    // If this doesn't work, it will throw an error upon trying to call a nil value.
    lmanager.register_luma_system_function(func_reg_check, "system_func_reg_check");
    lmanager.execute("__luma_system:system_func_reg_check()");
  }
}

/*
 * Databases
 * (Contain assets with integer identifiers)
 */
TEST_CASE("ObjectDatabase") {
  ObjectDatabase objdatabase;
  SUBCASE("Object id exists") {
    CHECK_EQ(objdatabase.object_id_exists(0), true);
    CHECK_EQ(objdatabase.object_id_exists(1), true);
    CHECK_EQ(objdatabase.object_id_exists(2), true);
    CHECK_EQ(objdatabase.object_id_exists(3), false);
  }
  SUBCASE("Object id has code") {
    CHECK_EQ(objdatabase.get_object_code(1).compare("x = 5"), 0);
    CHECK_EQ(objdatabase.get_object_code(3).compare(""), 0);
  }
  SUBCASE("Get ID from object names") {
    CHECK_EQ(objdatabase.get_object_id("objTest"), 0);
    CHECK_EQ(objdatabase.get_object_id("objTest2"), 1);
    CHECK_EQ(objdatabase.get_object_id("objDoesntExist"), -1);
  }
}

TEST_CASE("SpriteDatabase") {
  SpriteDatabase sprite_db;
  CHECK_EQ(sprite_db.sprite_exists("playerRun"), true);
  CHECK_EQ(sprite_db.sprite_exists("playerWalk"), false);
  CHECK_EQ(sprite_db.get_texture_manager().get_textures_size(), 2);
  CHECK_EQ(sprite_db.get_sprite_id("sprCat"), 1);
  CHECK_EQ(sprite_db.get_sprite_by_id(0)->get_texture_size().x, 320);
  CHECK_EQ(sprite_db.get_sprite_by_id(0)->get_texture_size().y, 80);
  CHECK_EQ(sprite_db.get_sprite_by_id(0)->get_subimage(1)->get_rect().left, 80);
  CHECK_EQ(sprite_db.get_sprite_by_id(0)->get_subimage(1)->get_rect().top, 0);
}

/**
 * UTILITY
 */
TEST_CASE("FileSystem") {
  SUBCASE("Existence check, basic file reading.") {
    CHECK_EQ(FileSystem::file_exists("hello.txt"), true);
    CHECK_EQ(FileSystem::file_exists("goodbye.txt"), false);
    CHECK_EQ(FileSystem::read_file("hello.txt").compare("hello\nworld"), 0);

    // Make sure reading a file that doesn't exist results in a thrown error
    bool error = false;
    try { FileSystem::read_file("goodbye.txt"); } catch (...) { error = true; }
    CHECK_EQ(error, true);
  }

  SUBCASE("Utilities") {
    CHECK_EQ(FileSystem::hex_string_to_uint("0"), 0);
    CHECK_EQ(FileSystem::hex_string_to_uint("ff0000"), 16711680);
    CHECK_EQ(FileSystem::hex_string_to_uint("FA842A"), 16417834);
  }

  SUBCASE("Read object file.") {
    CHECK_NE(FileSystem::load_object_file().compare(""), 0);
    CHECK_NE(FileSystem::read_file("objects.xml").compare(""), 0);
    CHECK_EQ(FileSystem::load_object_file().compare(FileSystem::read_file("objects.xml")), 0);
  }

  SUBCASE("Load window configuration file into window config object.") {
    ConfigManager conf_manager = FileSystem::load_config();
    CHECK_EQ(conf_manager.get_window_size().x, 320);
    CHECK_EQ(conf_manager.get_window_size().y, 240);
    CHECK_EQ(conf_manager.get_window_title().compare("Hello World!"), 0);
    CHECK_EQ(conf_manager.get_window_draw_color().r, 255);
    CHECK_EQ(conf_manager.get_window_draw_color().g, 0);
    CHECK_EQ(conf_manager.get_window_draw_color().b, 0);
  }

  SUBCASE("Load sprite database") {
    TextureManager texture_manager;
    std::vector<SpriteAsset> sprites = FileSystem::load_sprites(texture_manager);
    CHECK_EQ(sprites.size(), 2);
    CHECK_EQ(sprites.at(0).get_subimage_size().x, 80);
    CHECK_EQ(sprites.at(0).get_subimage_size().y, 80);
  }

  // Add checks for code etc
  SUBCASE("Load Objects from XML into vector of ObjectAssets") {
    std::vector<ObjectAsset*> objassets = FileSystem::load_objects();
    CHECK_EQ(objassets.at(0)->get_name().compare("objTest"), 0);
    CHECK_EQ(objassets.at(0)->get_id(), 0);
    CHECK_EQ(objassets.at(1)->get_name().compare("objTest2"), 0);
    CHECK_EQ(objassets.at(1)->get_id(), 1);
    CHECK_EQ(objassets.size(), 3);
  }
}


TEST_CASE("LuaLibrary") {
  ConfigManager conf = FileSystem::load_config();
  WindowManager window_manager(&conf);
  InputManager input_manager;
  ObjectDatabase obj_database;
  SpriteDatabase spr_database;
  LuaManager lmanager;
  lmanager.load_library(&obj_database, &window_manager, &spr_database, &input_manager);

  SUBCASE("Lua global library check"){
    lmanager.execute("__lua_library_var_check = lua_library_test()");
    CHECK_EQ(lmanager.get_global_int("__lua_library_var_check"), 42);
  }

  SUBCASE("Luma System library check"){
    lmanager.execute("__luma_system_var_check = __luma_system:luma_system_test()");
    CHECK_EQ(lmanager.get_global_int("__luma_system_var_check"), 65894);
  }

  SUBCASE("Database-dependant Luma System library check"){
    lmanager.execute("__object_id_check = __luma_system:get_object_id('objTest2')");
    CHECK_EQ(lmanager.get_global_int("__object_id_check"), 1);
  }

  SUBCASE("Instance creation check"){
    CHECK_EQ(lmanager.object_code_length(), 3);
    lmanager.execute("instance_create(objTest)");
    lmanager.execute("instance_create(objTest3)");
    lmanager.execute("instance_create(objTest)");
    lmanager.execute("instance_create(objTest2)");
    lmanager.execute("__luma_system:push_instances()");

    CHECK_EQ(lmanager.get_instance_count(), 4);
  }
}



/**
 * Visual / Realtime test
 */
TEST_CASE("Visual test") {
  printf("=============================================== Visual test.\n");
  ConfigManager conf = FileSystem::load_config();
  WindowManager window_manager(&conf);
  InputManager input_manager;
  ObjectDatabase obj_database;
  SpriteDatabase spr_database;
  LuaManager lmanager;

  CHECK_EQ(spr_database.get_texture_manager().get_textures_size(), 2);

  lmanager.load_library(&obj_database, &window_manager, &spr_database, &input_manager);
  lmanager.execute("instance_create(objTest)");

  SDL_Event e;
  while(window_manager.is_open()) {
      Uint32 ticks = SDL_GetTicks();
      while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) window_manager.close();
        input_manager.process_events(&e);
      }

      // process stuff
      lmanager.run_update_function();
      window_manager.clear();
      lmanager.run_draw_function();

      // vsync
      // TODO: replace "60" with FPS.
      Uint32 delay = (1000/60) - (SDL_GetTicks() - ticks);
      if(delay > (1000/60)) delay = (1000/60);
      SDL_Delay(delay);

      window_manager.display();
      input_manager.clear_pressed_keys();
  }
}
