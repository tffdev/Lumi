TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../include include external
DEPENDPATH += $$PWD/../../include include external
LIBS += -L$$PWD/../../lib/ -llua53 -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += \
        external/pugixml.cpp \
        source/configmanager.cpp \
        source/instanceasset.cpp \
        source/lualibrary.cpp \
        source/main.cpp \
        source/filesystem.cpp \
        source/luamanager.cpp \
        source/objectasset.cpp \
        source/objectdatabase.cpp \
        source/windowmanager.cpp

HEADERS += \
    external/pugixml.hpp \
    include/configmanager.h \
    include/filesystem.h \
    include/instanceasset.h \
    include/lualibrary.h \
    include/luamanager.h \
    include/objectasset.h \
    include/objectdatabase.h \
    include/windowmanager.h

# Run as test config
CONFIG += test

test {
    SOURCES -= source/main.cpp
    SOURCES += testing/tests.cpp
}



