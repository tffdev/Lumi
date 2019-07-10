TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/../../include include external
DEPENDPATH += $$PWD/../../include include external
LIBS += -L$$PWD/../../lib/ -llua53 -lsfml-graphics

SOURCES += \
        external/pugixml.cpp \
        source/configasset.cpp \
        source/lualibrary.cpp \
        source/main.cpp \
        source/filesystem.cpp \
        source/luamanager.cpp \
        source/objectasset.cpp \
        source/objectdatabase.cpp

HEADERS += \
    external/pugixml.hpp \
    include/configasset.h \
    include/filesystem.h \
    include/lualibrary.h \
    include/luamanager.h \
    include/objectasset.h \
    include/objectdatabase.h

# Run as test config
CONFIG += test

test {
    SOURCES -= source/main.cpp
    SOURCES += testing/tests.cpp
}



