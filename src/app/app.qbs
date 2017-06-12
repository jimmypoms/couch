import qbs 1.0

CouchApplication {
    name: "couchapp"

    files: [
        "*.cpp",
        "*.h",
        "view/qtquickcontrols2.conf",
        "view/resources.qrc",
        "view/*.qml",
        "view/images/*.svg",
        "view/components/*.qml",
        "view/controls/*.qml",
        "view/settings/*.qml",
        "view/music/*.qml",
        "view/translations/*.ts"
    ]

    Depends { name: "cpp" }
    Depends { name: "couch" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.gui" }
    Depends { name: "Qt.qml" }
    Depends { name: "Qt.quick" }
    Depends { name: "Qt.multimedia" }
    Depends { name: "Qt.network" }
}