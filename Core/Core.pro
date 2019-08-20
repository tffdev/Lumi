TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
CONFIG += static

INCLUDEPATH += $$PWD/../../include include external
DEPENDPATH += $$PWD/../../include include external
LIBS += -L$$PWD/../../lib/ \
-static -lsdl2  \
-lsdl2_image -lsdl2_mixer\
-lopengl32 \
-lmingw32 -mwindows -lm -ldinput8 \
-ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 \
-loleaut32 -lshell32 -lversion -luuid -static-libgcc \
-lhid -lsetupapi \
-lm

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
    source/managers/inputmanager.cpp \
    source/managers/luamanager.cpp \
    source/managers/roommanager.cpp \
    source/managers/windowmanager.cpp \
    source/databases/audiodatabase.cpp \
    source/databases/objectdatabase.cpp \
    source/databases/spritedatabase.cpp

SOURCES += external/luasrc/lcorolib.c \
external/luasrc/lfunc.c \
external/luasrc/lmathlib.c \
external/luasrc/lparser.c \
external/luasrc/lundump.c \
external/luasrc/lapi.c \
external/luasrc/lctype.c \
external/luasrc/lmem.c \
external/luasrc/ltablib.c \
external/luasrc/lgc.c \
external/luasrc/ltm.c \
external/luasrc/lutf8lib.c \
external/luasrc/lauxlib.c \
external/luasrc/ldblib.c \
external/luasrc/loadlib.c \
external/luasrc/lstate.c \
external/luasrc/lvm.c \
external/luasrc/ldebug.c \
external/luasrc/linit.c \
external/luasrc/lobject.c \
external/luasrc/lbaselib.c \
external/luasrc/liolib.c \
external/luasrc/lstring.c \
external/luasrc/lzio.c \
external/luasrc/lbitlib.c \
external/luasrc/ldo.c \
external/luasrc/llex.c \
external/luasrc/lopcodes.c \
external/luasrc/lcode.c \
external/luasrc/lstrlib.c \
external/luasrc/ldump.c \
external/luasrc/loslib.c \
external/luasrc/ltable.c \
external/luasrc/wmain.c

HEADERS += \
    external/pugixml.hpp \
    include/audioasset.h \
    include/audiodatabase.h \
    include/backgroundasset.h \
    include/backgrounddatabase.h \
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
CONFIG -= test

test {
    SOURCES -= source/main.cpp
    SOURCES += testing/tests.cpp
}


RESOURCES += resources.qrc



