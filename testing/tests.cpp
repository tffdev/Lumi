#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <filesystem.h>
#include <xmlfile.h>
#include <objectasset.h>

int main() {
    doctest::Context context;
    return context.run();
}

TEST_CASE("Sanity Check") {
    CHECK(1 == 1);
    SUBCASE("Nested Sanity Check") {
        CHECK(4 == 4);
    }
}

TEST_CASE("File System") {
    SUBCASE("Existence check, basic file reading.") {
        CHECK_EQ(FileSystem::file_exists("data/test_data/hello.txt"), true);
        CHECK_NE(FileSystem::file_exists("data/test_data/goodbye.txt"), true);
        CHECK_EQ(FileSystem::read_file("data/test_data/hello.txt").compare("hello\nworld"), 0);
        CHECK_NE(FileSystem::read_file("data/test_data/goodbye.txt").compare("hello\nworld"), 0);
    }
    SUBCASE("Read object file.") {
        CHECK_NE(FileSystem::load_object_file().compare(""), 0);
        CHECK_NE(FileSystem::read_file("data/test_data/note.xml").compare(""), 0);
        CHECK_EQ(FileSystem::load_object_file().compare(FileSystem::read_file("data/test_data/note.xml")), 0);
    }
}

TEST_CASE("Object asset class.") {
    ObjectAsset asset("objTest", "x = 5", "sprTest");
    CHECK_EQ(asset.has_code(), true);
    CHECK_EQ(asset.has_default_sprite(), true);
    CHECK_EQ(asset.get_name().compare("objTest"), 0);
    CHECK_EQ(asset.get_code().compare("x = 5"), 0);
    CHECK_EQ(asset.get_default_sprite().compare("sprTest"), 0);

    ObjectAsset asset2("objTest2");
    CHECK_EQ(asset2.has_code(), false);
    CHECK_EQ(asset2.has_default_sprite(), false);
    CHECK_EQ(asset2.get_name().compare("objTest2"), 0);
    CHECK_EQ(asset2.get_code().compare(""), 0);
    CHECK_EQ(asset2.get_default_sprite().compare(""), 0);
}

TEST_CASE("XML Loader") {

}
