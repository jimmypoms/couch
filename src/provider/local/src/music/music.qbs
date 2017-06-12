import qbs 1.0

CouchLibrary {
    name: "localmusicprovider"
    destinationDirectory: project.buildDirectory + "/lib/couch/provider"

    files: [
        "../common/localprovider.cpp",
        "../common/localprovider.h",
        "localmusicprovider.cpp",
        "localmusicprovider.h",
        "trackmetadatafetcher.cpp",
        "trackmetadatafetcher.h",
        "resources.qrc"
    ]

    Depends { name: "cpp" }
    Depends { name: "couch" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.concurrent" }

    cpp.defines: ["QT_NO_KEYWORDS"]
    cpp.dynamicLibraries: [
        "xapian",
        "mediainfo",
        "dl"
    ]
}