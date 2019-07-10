#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <filesystem.h>
#include <objectasset.h>
#include <luamanager.h>
#include <configasset.h>

TEST_CASE("Sanity Check") {
    CHECK(1 == 1);
    SUBCASE("Nested Sanity Check") {
        CHECK(4 == 4);
    }
}

TEST_CASE("ObjectAsset") {
    ObjectAsset asset("objTest", "sprTest");
    CHECK_EQ(asset.has_default_sprite(), true);
    CHECK_EQ(asset.get_name().compare("objTest"), 0);
    CHECK_EQ(asset.get_default_sprite().compare("sprTest"), 0);

    ObjectAsset asset2("objTest2");
    CHECK_EQ(asset2.has_default_sprite(), false);
    CHECK_EQ(asset2.get_name().compare("objTest2"), 0);
    CHECK_EQ(asset2.get_default_sprite().compare(""), 0);
}

TEST_CASE("ConfigAsset") {
    ConfigAsset asset("Hello", 320, 240, 0x32d61cff);
    CHECK_EQ(asset.get_window_size().x, 320);
    CHECK_EQ(asset.get_window_size().y, 240);
    CHECK_EQ(asset.get_window_title().compare("Hello"), 0);
    CHECK_EQ(asset.get_window_draw_color().r, 50);
    CHECK_EQ(asset.get_window_draw_color().g, 214);
    CHECK_EQ(asset.get_window_draw_color().b, 28);
    CHECK_EQ(asset.get_window_draw_color().a, 255);
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
        ConfigAsset asset = FileSystem::load_config();
        CHECK_EQ(asset.get_window_size().x, 320);
        CHECK_EQ(asset.get_window_size().y, 240);
        CHECK_EQ(asset.get_window_title().compare("Hello World!"), 0);
        CHECK_EQ(asset.get_window_draw_color().r, 255);
        CHECK_EQ(asset.get_window_draw_color().g, 0);
        CHECK_EQ(asset.get_window_draw_color().b, 0);
    }
    SUBCASE("Load Objects from XML into vector of ObjectAssets") {
        std::vector<ObjectAsset*> objassets = FileSystem::load_objects();
        CHECK_EQ(objassets.at(0)->get_name().compare("objTest"), 0);
        CHECK_EQ(objassets.at(1)->get_name().compare("objTest2"), 0);
        CHECK_EQ(objassets.size(), 2);
    }
}

int func_reg_check(lua_State *L) {
    lua_pushnumber(L, 68923);
    return 1;
}

TEST_CASE("LuaManager") {
    LuaManager lmanager;
    SUBCASE("Lua execution check") {
        lmanager.execute("lua_execute_check = 370439");
        CHECK_EQ(lmanager.get_global_int("lua_execute_check"), 370439);
        CHECK_EQ(lmanager.get_global_int("nonexistant_variable_check"), 0);
    }
    SUBCASE("Load main and objects check"){
        CHECK_EQ(lmanager.get_global_int("lua_main_check"), 983652);
        CHECK_EQ(lmanager.get_global_int("lua_objects_check"), 345897);
        CHECK_EQ(lmanager.get_global_int("objTest"), 1);
        CHECK_EQ(lmanager.get_global_int("objTest2"), 2);
        lmanager.execute("instance_create(objTest)");
        lmanager.update();
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
    }
}








