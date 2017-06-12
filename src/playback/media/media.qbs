import qbs 1.0

CouchLibrary {
    name: "mediaplaybackhandler"
    destinationDirectory: project.buildDirectory + "/lib/couch/playback"

    files: [
        "src/mediaplaybackhandler.cpp",
        "src/mediaplaybackhandler.h"
    ]

    Depends { name: "cpp" }
    Depends { name: "couch" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.multimedia" }
}