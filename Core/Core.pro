TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../include include external
DEPENDPATH += $$PWD/../../include include external
LIBS += -L$$PWD/../../lib/ -llua53 -lsfml-graphics -lsfml-window -lsfml-system -lsdl2 -lopengl32 -lsdl2_image -lsdl2_mixer

SOURCES += \
        external/pugixml.cpp \
        source/assets/audioasset.cpp \
    source/assets/backgroundasset.cpp \
        source/assets/hitboxasset.cpp \
        source/assets/objectasset.cpp \
    source/assets/roomasset.cpp \
        source/assets/spriteasset.cpp \
        source/assets/subimagerect.cpp \
        source/assets/textureasset.cpp \
    source/assets/tilesetasset.cpp \
    source/databases/backgrounddatabase.cpp \
    source/databases/roomdatabase.cpp \
    source/databases/tilesetdatabase.cpp \
    source/engine.cpp \
        source/lualibrary.cpp \
        source/main.cpp \
        source/filesystem.cpp \
        source/managers/configmanager.cpp \
        source/managers/inputmanager.cpp \
        source/managers/luamanager.cpp \
    source/managers/roommanager.cpp \
        source/managers/windowmanager.cpp \
        source/databases/audiodatabase.cpp \
        source/databases/objectdatabase.cpp \
        source/databases/spritedatabase.cpp \

HEADERS += \
    external/pugixml.hpp \
    include/audioasset.h \
    include/audiodatabase.h \
    include/backgroundasset.h \
    include/backgrounddatabase.h \
    include/configmanager.h \
    include/engine.h \
    include/filesystem.h \
    include/hitboxasset.h \
    include/inputmanager.h \
    include/lualibrary.h \
    include/luamanager.h \
    include/mathlibrary.h \
    include/objectasset.h \
    include/objectdatabase.h \
    include/roomasset.h \
    include/roomdatabase.h \
    include/roommanager.h \
    include/spriteasset.h \
    include/spritedatabase.h \
    include/subimagerect.h \
    include/textureasset.h \
    include/tilesetasset.h \
    include/tilesetdatabase.h \
    include/windowmanager.h

# Run as test config
CONFIG += test

test {
    SOURCES -= source/main.cpp
    SOURCES += testing/tests.cpp
}



