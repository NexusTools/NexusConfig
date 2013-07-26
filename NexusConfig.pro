#-------------------------------------------------
#
# Project created by QtCreator 2013-07-26T12:18:30
#
#-------------------------------------------------

QT       += script xml sql

QT       -= gui

!greaterThan(QT_MAJOR_VERSION, 4) {
	QT += gui
	DEFINES += QSETTINGSLOCATION
}

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
