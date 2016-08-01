TEMPLATE = app
TARGET = couch

CLIBDESTDIR = ../../lib/couch
CBINDESTDIR = ../../bin
CINCLUDEPATH = ../../include

CONFIG(debug, debug|release) {
    CBUILDDIR = ../../build/debug
    QMAKE_RPATHDIR += $$CLIBDESTDIR
    QMAKE_RPATHDIR += lib/couch
} else {
    CBUILDDIR = ../../build/release
}

OBJECTS_DIR = $$CBUILDDIR/.obj
MOC_DIR = $$CBUILDDIR/.moc
RCC_DIR = $$CBUILDDIR/.rcc
UI_DIR = $$CBUILDDIR/.ui

QT += core gui qml quick multimedia network
QMAKE_RPATHDIR += ../lib/couch

CONFIG += c++11
CONFIG += debug_and_release
DESTDIR = $$CBINDESTDIR

DEPENDPATH += $$CINCLUDEPATH
INCLUDEPATH += $$CINCLUDEPATH
LIBS += -L$$CLIBDESTDIR -lcouch

SOURCES += main.cpp \
    couch.cpp \
    playback/media/mediaplaybackhandler.cpp \
    playback/youtube/youtubeplaybackhandler.cpp

HEADERS += \
    couch.h \
    playback/media/mediaplaybackhandler.h \
    playback/youtube/youtubeplaybackhandler.h

RESOURCES += view/resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

OTHER_FILES +=
