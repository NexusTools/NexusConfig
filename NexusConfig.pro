#-------------------------------------------------
#
# Project created by QtCreator 2013-07-26T12:18:30
#
#-------------------------------------------------

# Qt Modules
QT       += script xml sql

QT       -= gui

!greaterThan(QT_MAJOR_VERSION, 4) {
	QT += gui
	DEFINES += LEGACY_QT
}

# Project Information
TARGET = NexusConfig
TEMPLATE = lib

DEFINES += NEXUSCONFIG_LIBRARY

# Versioning
include(version.pri)

# Project Files
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
