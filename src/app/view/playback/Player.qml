import QtQuick 2.0
import QtMultimedia 5.5

import "../components"

FocusScope {
    id: root
    focus: true

    signal backClicked

    property color highlightColor: "black"
    property real highlightOpacity: 0.5

    Rectangle {
        anchors.fill: parent
        color: "black"
        VideoOutput {
            id: playerView
            fillMode: VideoOutput.PreserveAspectFit
            anchors.fill: parent
            source: player
        }
    }

    PlayerOverlay {
        anchors.fill: parent
    }

    Keys.onBackPressed: {
        root.backClicked()
    }
    Keys.onEscapePressed: {
        root.backClicked()
    }
}
