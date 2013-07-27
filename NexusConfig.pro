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
	DEFINES += QSETTINGSLOCATION
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
