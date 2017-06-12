import qbs 1.0

CouchLibrary {
    name: "youtubeplaybackhandler"
    destinationDirectory: project.buildDirectory + "/lib/couch/playback"

    files: [
        "src/youtubeplaybackhandler.cpp",
        "src/youtubeplaybackhandler.h"
    ]

    Depends { name: "couch" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.multimedia" }
    Depends { name: "Qt.network" }
}