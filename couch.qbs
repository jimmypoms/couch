Project {
    qbsSearchPaths: "qbs"
    minimumQbsVersion: "1.6.0"

    references: [
        "src/core/core.qbs",
        "src/provider/provider.qbs",
        "src/playback/playback.qbs",
        "src/qml/qml.qbs",
        "src/app/app.qbs"
    ]
}