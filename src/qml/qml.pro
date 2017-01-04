TEMPLATE = lib
TARGET = qmlcouchplugin
DESTDIR = ../../imports/Couch

CLIBDIR = ../../lib/couch
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

QT += core qml multimedia

CONFIG += c++11
CONFIG += plugin
CONFIG += debug_and_release

QMAKE_RPATHDIR += $$CLIBDIR
DEPENDPATH += $$CINCLUDEPATH
INCLUDEPATH += $$CINCLUDEPATH
LIBS += -L$$CLIBDIR -lcouch

HEADERS += qmlcouchplugin.h

couch.files = qmldir
couch.path = ../../imports/Couch
INSTALLS += couch