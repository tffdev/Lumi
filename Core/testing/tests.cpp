#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <filesystem.h>
#include <objectasset.h>
#include <luamanager.h>
#include <configmanager.h>
#include <objectdatabase.h>
#include <lualibrary.h>
#include <windowmanager.h>

TEST_CASE("Sanity Check") {
    CHECK(1 == 1);
    SUBCASE("Nested Sanity Check") {
        CHECK(4 == 4);
    }
}

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

int func_reg_check(lua_State *L) {
    lua_pushnumber(L, 68923);
    return 1;
}

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

TEST_CASE("WindowManager") {
    ConfigManager config("hi", 320, 240, 0xff0000);
    WindowManager window_manager(&config);
    CHECK_EQ(window_manager.is_open(), true);
    CHECK_EQ(window_manager.get_size().x, 320);
    CHECK_EQ(window_manager.get_size().y, 240);
    window_manager.close();
    CHECK_EQ(window_manager.is_open(), false);
}

TEST_CASE("LuaManager") {
    ObjectDatabase obj_database;
    LuaManager lmanager;
    WindowManager window_manager(new ConfigManager("hi", 320, 240, 0xff0000ff), true);
    lmanager.load_library(&obj_database, &window_manager);

    SUBCASE("Lua execution check") {
        lmanager.execute("___lua_execute_check = 370439");
        CHECK_EQ(lmanager.get_global_int("___lua_execute_check"), 370439);
        CHECK_EQ(lmanager.get_global_int("nonexistant_variable_check"), 0);
    }
    SUBCASE("Load main and objects check"){
        CHECK_EQ(lmanager.get_global_int("___lua_main_check"), 983652);
        CHECK_EQ(lmanager.get_global_int("objTest"), 0);
        CHECK_EQ(lmanager.get_global_int("objTest2"), 1);
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

TEST_CASE("LuaLibrary") {
    ObjectDatabase obj_database;
    LuaManager lmanager;
    ConfigManager conf = FileSystem::load_config();
    WindowManager window_manager(&conf, true);
    lmanager.load_library(&obj_database, &window_manager);

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
        lmanager.run_update_function();
        lmanager.run_draw_function();

        while(window_manager.is_open()) {
            sf::Event e;
            while(window_manager.poll_events(e)){
                if(e.type == sf::Event::Closed) window_manager.close();
            }
            window_manager.clear();

            lmanager.run_draw_function();

            window_manager.display();
        }
    }
}
