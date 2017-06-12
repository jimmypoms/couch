import qbs 1.0

CouchLibrary {
    name: "couch"

    files: [
        "couch/*.cpp",
        "couch/*.h",
        "model/*.cpp",
        "model/*.h",
        "movie/*.cpp",
        "movie/*.h",
        "multimedia/*.cpp",
        "multimedia/*.h",
        "music/*.cpp",
        "music/*.h",
        "settings/*.cpp",
        "settings/*.h"
    ]

    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.network" }
    Depends { name: "Qt.multimedia" }

    cpp.defines: ["COUCH_LIBRARY"]
}
