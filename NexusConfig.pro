#-------------------------------------------------
#
# Project created by QtCreator 2013-07-26T12:18:30
#
#-------------------------------------------------

QT       += script xml

QT       -= gui

TARGET = NexusConfig
TEMPLATE = lib

DEFINES += NEXUSCONFIG_LIBRARY

SOURCES += nexusconfig.cpp

HEADERS += nexusconfig.h\
        nexusconfig_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
