TEMPLATE = lib
TARGET = vodo

CONFIG(debug, debug|release) {
    CBUILDDIR = ../../../build/debug
    QMAKE_CFLAGS+=-pg
    QMAKE_CXXFLAGS+=-pg
    QMAKE_LFLAGS+=-pg
    LIBS += -lprofiler
} else {
    CBUILDDIR = ../../../build/release
}

OBJECTS_DIR = $$CBUILDDIR/.obj
MOC_DIR = $$CBUILDDIR/.moc
RCC_DIR = $$CBUILDDIR/.rcc
UI_DIR = $$CBUILDDIR/.ui

CLIBDESTDIR = ../../../lib/couch
CINCLUDEPATH = ../../../include

QT += core network
QMAKE_RPATHDIR += $$CLIBDESTDIR/service

CONFIG += c++11
CONFIG += plugin
CONFIG += debug_and_release
CONFIG += no_keywords
DESTDIR = $$CLIBDESTDIR/provider

DEFINES += COUCH_SERVICE_MOVIE_LIBRARY

DEPENDPATH += $$CINCLUDEPATH
INCLUDEPATH += $$CINCLUDEPATH
LIBS += -L$$CLIBDESTDIR -lcouch -L$$CLIBDESTDIR/service

SOURCES += \
    src/movie/vodoprovider.cpp

HEADERS += \
    src/movie/vodoprovider.h

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
OTHER_FILES +=
