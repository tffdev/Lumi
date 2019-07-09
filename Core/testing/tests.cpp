#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <filesystem.h>
#include <objectasset.h>
#include <luamanager.h>

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

TEST_CASE("FileSystem") {
    SUBCASE("Existence check, basic file reading.") {
        CHECK_EQ(FileSystem::file_exists("hello.txt"), true);
        CHECK_NE(FileSystem::file_exists("goodbye.txt"), true);
        CHECK_EQ(FileSystem::read_file("hello.txt").compare("hello\nworld"), 0);
        CHECK_NE(FileSystem::read_file("goodbye.txt").compare("hello\nworld"), 0);
    }
    SUBCASE("Read object file.") {
        CHECK_NE(FileSystem::load_object_file().compare(""), 0);
        CHECK_NE(FileSystem::read_file("objects.xml").compare(""), 0);
        CHECK_EQ(FileSystem::load_object_file().compare(FileSystem::read_file("objects.xml")), 0);
    }

    SUBCASE("Load window configuration file into window config object.") {

    }

    SUBCASE("Load Objects from XML into vector of ObjectAssets") {
        std::vector<ObjectAsset*> objassets = FileSystem::load_objects();
        CHECK_EQ(objassets.at(0)->get_name().compare("objTest"), 0);
        CHECK_EQ(objassets.at(1)->get_name().compare("objTest2"), 0);
        CHECK_EQ(objassets.size(), 2);
    }
}

TEST_CASE("LuaManager") {
    LuaManager lmanager;
    CHECK_EQ(lmanager.get_global_int("lua_main_check"), 983652);
    CHECK_EQ(lmanager.get_global_int("lua_objects_check"), 345897);
    lmanager.execute("lua_execute_check = 370439");
    CHECK_EQ(lmanager.get_global_int("lua_execute_check"), 370439);
}








