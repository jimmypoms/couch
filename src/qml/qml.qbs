import qbs 1.0

CouchLibrary {
    name: "qmlcouchplugin"
    destinationDirectory: project.buildDirectory + "/imports/Couch"
    type: ["dynamiclibrary", "qmldir"]

    files: [
        "qmlcouchplugin.h",
        "qmldir"
    ]

    Depends { name: "cpp" }
    Depends { name: "couch" }
    Depends { name: "qmldir" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.multimedia" }
    Depends { name: "Qt.qml" }

    cpp.defines: ["QT_PLUGIN"]
}