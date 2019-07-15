TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../include include external
DEPENDPATH += $$PWD/../../include include external
LIBS += -L$$PWD/../../lib/ -llua53 -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += \
        external/pugixml.cpp \
        source/assets/hitboxasset.cpp \
        source/assets/instanceasset.cpp \
        source/assets/objectasset.cpp \
        source/assets/spriteasset.cpp \
        source/assets/subimagerect.cpp \
        source/assets/textureasset.cpp \
        source/lualibrary.cpp \
        source/main.cpp \
        source/filesystem.cpp \
        source/managers/configmanager.cpp \
        source/managers/luamanager.cpp \
        source/managers/texturemanager.cpp \
        source/managers/windowmanager.cpp \
        source/objectdatabase.cpp \
        source/spritedatabase.cpp

HEADERS += \
    external/pugixml.hpp \
    include/configmanager.h \
    include/filesystem.h \
    include/hitboxasset.h \
    include/instanceasset.h \
    include/lualibrary.h \
    include/luamanager.h \
    include/objectasset.h \
    include/objectdatabase.h \
    include/spriteasset.h \
    include/spritedatabase.h \
    include/subimagerect.h \
    include/textureasset.h \
    include/texturemanager.h \
    include/windowmanager.h

# Run as test config
CONFIG += test

test {
    SOURCES -= source/main.cpp
    SOURCES += testing/tests.cpp
}



