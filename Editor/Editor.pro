#-------------------------------------------------
#
# Project created by QtCreator 2019-08-18T14:56:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
RC_ICONS = Lumi.ico

SOURCES += \
        external/pugixml.cpp \
        source/assettree.cpp \
        source/editors/configurationeditor.cpp \
        source/editors/objecteditor.cpp \
        source/editors/spriteeditor.cpp \
        source/editortabs.cpp \
        source/filesystem.cpp \
        source/main.cpp \
        source/mainwindow.cpp \
        source/projectdata.cpp \
        source/projectloader.cpp \
        source/projectrunner.cpp \
        source/projectsaver.cpp \
        source/toplevelmanager.cpp

HEADERS += \
        external/pugixml.hpp \
        include/asset_types.h \
        include/assettree.h \
        include/editors/configurationeditor.h \
        include/editors/spriteeditor.h \
        include/editors/objecteditor.h \
        include/editortabs.h \
        include/filesystem.h \
        include/mainwindow.h \
        include/projectdata.h \
        include/projectloader.h \
        include/projectrunner.h \
        include/projectsaver.h \
        include/toplevelmanager.h

FORMS += \
        forms/configurationeditor.ui \
        forms/mainwindow.ui \
        forms/objecteditor.ui \
        forms/spriteeditor.ui

INCLUDEPATH += include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

include(style.css)
