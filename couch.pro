TEMPLATE = subdirs

SUBDIRS = \
    src/core \
    src/provider \
    src/playback \
    src/qml \
    src/app

CONFIG += ordered thread debug_and_release

INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib
