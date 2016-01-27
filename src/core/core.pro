TEMPLATE = lib
TARGET = couch

CONFIG(debug, debug|release) {
    CBUILDDIR = ../../build/debug
} else {
    CBUILDDIR = ../../build/release
}

OBJECTS_DIR = $$CBUILDDIR/.obj
MOC_DIR = $$CBUILDDIR/.moc
RCC_DIR = $$CBUILDDIR/.rcc
UI_DIR = $$CBUILDDIR/.ui

CLIBDESTDIR = ../../lib/couch

QT += core network multimedia

CONFIG += c++11
CONFIG += debug_and_release
DESTDIR = $$CLIBDESTDIR

DEFINES += COUCH_LIBRARY

SOURCES += \
    couch/cycliccache.cpp \
    couch/serializableclass.cpp \
    model/service.cpp \
    model/provider.cpp \
    model/networkprovider.cpp \
    model/couchitemlist.cpp \
    model/couchsourcelist.cpp \
    model/couchrequest.cpp \
    model/filter.cpp \
    model/source.cpp \
    model/item.cpp \
    model/itemmetadata.cpp \
    model/metadataplugin.cpp \
    multimedia/playbackhandler.cpp \
    multimedia/playbackhandlerinterface.cpp \
    multimedia/couchplayer.cpp \
    movie/movie.cpp \
    movie/moviefilter.cpp \
    movie/moviemetadata.cpp \
    movie/movieservice.cpp \
    movie/movieprovider.cpp \
    movie/movienetworkprovider.cpp

HEADERS += \
    couch/cycliccache.h \
    couch/serializableclass.h \
    model/service.h \
    model/provider.h \
    model/networkprovider.h \
    model/couchitemlist.h \
    model/couchsourcelist.h \
    model/couchrequest.h \
    model/filter.h \
    model/source.h \
    model/item.h \
    model/itemmetadata.h \
    model/metadataplugin.h \
    multimedia/playbackhandler.h \
    multimedia/playbackhandlerinterface.h \
    multimedia/couchplayer.h \
    movie/movie.h \
    movie/moviefilter.h \
    movie/moviemetadata.h \
    movie/movieservice.h \
    movie/movieprovider.h \
    movie/movienetworkprovider.h

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
OTHER_FILES +=
