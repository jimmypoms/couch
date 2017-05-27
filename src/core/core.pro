TEMPLATE = lib
TARGET = couch

CLIBDESTDIR = ../../lib/couch
CBINDESTDIR = ../../bin
CINCLUDEPATH = ../../include

CONFIG(debug, debug|release) {
    CBUILDDIR = ./build/debug
} else {
    CBUILDDIR = ./build/release
}

OBJECTS_DIR = $$CBUILDDIR/.obj
MOC_DIR = $$CBUILDDIR/.moc
RCC_DIR = $$CBUILDDIR/.rcc
UI_DIR = $$CBUILDDIR/.ui

QT += core network multimedia

CONFIG += c++11
CONFIG += debug_and_release
DESTDIR = $$CLIBDESTDIR

DEPENDPATH += $$CLIBDESTDIR
INCLUDEPATH += $$CINCLUDEPATH

DEFINES += COUCH_LIBRARY

SOURCES += \
    couch/cycliccache.cpp \
    couch/serializableclass.cpp \
    model/service.cpp \
    model/provider.cpp \
    model/networkprovider.cpp \
    model/couchitemlist.cpp \
    model/couchsourcelist.cpp \
    model/couchproviderlist.cpp \
    model/couchactionlist.cpp \
    model/couchaction.cpp \
    model/couchplayaction.cpp \
    model/couchrequest.cpp \
    model/filter.cpp \
    model/source.cpp \
    model/item.cpp \
    model/itemmetadata.cpp \
    model/metadataplugin.cpp \
    settings/setting.cpp \
    settings/settinglist.cpp \
    settings/foldersetting.cpp \
    multimedia/playbackhandler.cpp \
    multimedia/playbackhandlerinterface.cpp \
    multimedia/couchplayer.cpp \
    multimedia/couchplaylist.cpp \
    movie/movie.cpp \
    movie/moviefilter.cpp \
    movie/moviemetadata.cpp \
    movie/movieservice.cpp \
    movie/movieprovider.cpp \
    movie/movienetworkprovider.cpp \
    music/artist.cpp \
    music/artistmetadata.cpp \
    music/album.cpp \
    music/albummetadata.cpp \
    music/track.cpp \
    music/trackmetadata.cpp \
    music/musicfilter.cpp \
    music/musicservice.cpp \
    music/musicprovider.cpp \
    music/musicnetworkprovider.cpp

HEADERS += \
    couch/cycliccache.h \
    couch/serializableclass.h \
    model/service.h \
    model/provider.h \
    model/networkprovider.h \
    model/couchitemlist.h \
    model/couchsourcelist.h \
    model/couchproviderlist.h \
    model/couchactionlist.h \
    model/couchaction.h \
    model/couchplayaction.h \
    model/couchrequest.h \
    model/filter.h \
    model/source.h \
    model/item.h \
    model/itemmetadata.h \
    model/metadataplugin.h \
    settings/setting.h \
    settings/settinglist.h \
    settings/foldersetting.h \
    multimedia/playbackhandler.h \
    multimedia/playbackhandlerinterface.h \
    multimedia/couchplayer.h \
    multimedia/couchplaylist.h \
    movie/movie.h \
    movie/moviefilter.h \
    movie/moviemetadata.h \
    movie/movieservice.h \
    movie/movieprovider.h \
    movie/movienetworkprovider.h \
    music/artist.h \
    music/artistmetadata.h \
    music/album.h \
    music/albummetadata.h \
    music/track.h \
    music/trackmetadata.h \
    music/musicfilter.h \
    music/musicservice.h \
    music/musicprovider.h \
    music/musicnetworkprovider.h

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
OTHER_FILES +=
