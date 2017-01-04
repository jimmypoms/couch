import QtQuick 2.4
import QtMultimedia 5.5

import Couch 1.0

Rectangle {
    VideoOutput {
        fillMode: VideoOutput.PreserveAspectFit
        anchors.fill: parent
        source: player
    }
}
