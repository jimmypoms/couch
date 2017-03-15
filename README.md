# Couch

Couch is a home theater software which allows you to combine different content provider into one convenient interface.

```
Please beware that Couch is still very much in alpha. This means that a lot of very basic features are not yet ready to be used.
```

## Goals

*   Combine multiple music content providers such as Spotify, SoundCloud, Youtube
*   Combine multiple tv series content providers into one
*   Combine multiple movie content providers into one
*   Focused on being used on a tv in the living room
*   Fully usable with a simple remote (D-Pad, Back)
*   Fully usable on low end devices such as the Raspberry Pi

## Non goals

*   Couch is not meant to be a content provider itself
*   Couch is not meant to be a replacement for media center software such as Kodi, Plex, MediaPortal

## Building

### Dependecies

The following dependencies are needed to build couch on a debian based system.

    build-essential
    qtbase5-dev
    qtmultimedia5-dev
    qtdeclarative5-dev

Additianally for the local file provider the following packages are needed.

    libxapian-dev
    libmediainfo-dev

Couch does support the [Qt Virtual Keyboard](http://doc.qt.io/qt-5/qtvirtualkeyboard-index.html). On debian systems you will need to build it yourself since it is not yet part of the official repositories.

## Running

### Dependencies

    libqt5core5a
    libqt5xml5
    libqt5network5
    libqt5multimedia5
    libqt5multimedia5-plugins
    libqt5concurrent5
    libqt5quick5
    qml-module-qtquick2
    qml-module-qtquick-window2
    qml-module-qtquick-layouts
    qml-module-qtquick-controls2
    qml-module-qtquick-templates2
    qml-module-qtgraphicaleffects
    qml-module-qtmultimedia
    libxapian30
    libmediainfo0v5

## Source code structure

### Navigating the source

The source tree is devided into the folowing different components.

* **app** contains all the application specific logic such as loading the provider/playback plugins and the QML view part
* **core** contains the core library
* **playback** contains the playback handlers that are part of the core couch application as seperate qt library projects
* **provider** contains the provider that are part of the core couch application as seperate qt library projects

### Design

Architecturaly the couch core library is seperated into the following concepts:

* **service**: A service represents a given type of media (e.g. music, tv shows, movies, ...)
* **provider**: A provider is a source of media of a given type (e.g. Spotify for music)
* **playback handler**: A playback handler allows a specific format to be played (e.g. Youtube links, mp3 files, ...)
* **item**: The Item class is the parent class of any media (e.g. Artist, Album, Movie)
* **metadata**: The Metadata class represents the metadata information of an item (e.g. Movie description, rating, list of directors, ...)
* **source**: The Source class contains the actual playable file for an item
