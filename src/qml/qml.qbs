import qbs 1.0

CouchLibrary {
    name: "qmlcouchplugin"
    destinationDirectory: project.buildDirectory + "/imports/Couch"

    files: [
        "qmlcouchplugin.h"
    ]

    Depends { name: "cpp" }
    Depends { name: "couch" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.multimedia" }
    Depends { name: "Qt.qml" }

    cpp.defines: ["QT_PLUGIN"]

    Group {
        name: "qmldir resource"
        files: "qmldir"
        qbs.install: true
        qbs.installDir: destinationDirectory
    }
}