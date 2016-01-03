import QtQuick 2.2
import QtQuick.Controls 1.2

import "components"
import "content"

ApplicationWindow {
    visible: true
    visibility: "FullScreen"
    flags: Qt.FramelessWindowHint
    width: dp(1024)
    height: dp(768)

    Background {
        id: backgroundView
        anchors.fill: parent
        color: "#193441"
    }

    CouchIndicator {
        anchors.centerIn: parent
    }
}