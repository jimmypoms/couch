TEMPLATE = lib
TARGET = localmusicprovider

CONFIG(debug, debug|release) {
    CBUILDDIR = ./build/debug
} else {
    CBUILDDIR = ./build/release
}

OBJECTS_DIR = $$CBUILDDIR/.obj
MOC_DIR = $$CBUILDDIR/.moc
RCC_DIR = $$CBUILDDIR/.rcc
UI_DIR = $$CBUILDDIR/.ui

CLIBDESTDIR = ../../../../../lib/couch
CINCLUDEPATH = ../../../../../include

QT += core concurrent
QMAKE_RPATHDIR += $$CLIBDESTDIR/service

CONFIG += c++11
CONFIG += plugin
CONFIG += debug_and_release
CONFIG += no_keywords
DESTDIR = $$CLIBDESTDIR/provider

DEPENDPATH += $$CINCLUDEPATH
INCLUDEPATH += $$CINCLUDEPATH
LIBS += -L$$CLIBDESTDIR -lcouch -L$$CLIBDESTDIR/service -lxapian -lmediainfo

SOURCES += \
    ../common/localprovider.cpp \
    localmusicprovider.cpp \
    trackmetadatafetcher.cpp

HEADERS += \
    ../common/localprovider.h \
    localmusicprovider.h \
    trackmetadatafetcher.h

RESOURCES = resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
OTHER_FILES +=
