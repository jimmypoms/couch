TEMPLATE = lib
TARGET = youtubeplaybackhandler

CONFIG(debug, debug|release) {
    CBUILDDIR = ./build/debug
} else {
    CBUILDDIR = ./build/release
}

OBJECTS_DIR = $$CBUILDDIR/.obj
MOC_DIR = $$CBUILDDIR/.moc
RCC_DIR = $$CBUILDDIR/.rcc
UI_DIR = $$CBUILDDIR/.ui

CLIBDESTDIR = ../../../lib/couch
CINCLUDEPATH = ../../../include

QT += core multimedia

CONFIG += c++11
CONFIG += plugin
CONFIG += debug_and_release
CONFIG += no_keywords
DESTDIR = $$CLIBDESTDIR/playback

DEPENDPATH += $$CINCLUDEPATH
INCLUDEPATH += $$CINCLUDEPATH
LIBS += -L$$CLIBDESTDIR -lcouch

SOURCES += \
    src/youtubeplaybackhandler.cpp

HEADERS += \
    src/youtubeplaybackhandler.h

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
OTHER_FILES +=
