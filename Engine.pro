TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L$$PWD/../lib/ -llua53 -lsfml-graphics
INCLUDEPATH += $$PWD/../include include external
DEPENDPATH += $$PWD/../include

VPATH += source

SOURCES += \
        main.cpp \
        source/filesystem.cpp \
        source/objectasset.cpp \
        source/xmlfile.cpp \
        external/pugixml.cpp

HEADERS += \
    include/filesystem.h \
    include/objectasset.h \
    include/xmlfile.h \
    external/pugixml.hpp \

# Run as test config
CONFIG += test

test {
    SOURCES -= main.cpp
    SOURCES += testing/tests.cpp
}
