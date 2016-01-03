import QtQuick 2.0

import "../components"

FocusScope {
    id: container

    property alias highlightColor: curtain.color
    property alias highlightOpacity: curtain.opacity

    signal backClicked

    Rectangle {
        id: curtain
        anchors.fill: parent
    }

    Rectangle {
        id: header
        color: highlightColor
        opacity: highlightOpacity

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: dp(40)
    }

    Row {
        anchors.fill: header
        spacing: dp(5)

        CouchIconButton {
            id: closeButton
            focus: true
            focusColor: "grey"
            size: dp(40)
            anchors.verticalCenter: parent.verticalCenter

            source: "../images/icon-back.svg"
            onClicked: {
                container.backClicked();
            }
        }

        Text {
            id: title
            anchors.verticalCenter: parent.verticalCenter
            text: player.currentSource ? player.currentSource.name : ''
            color: "white"
            font.weight: Font.Normal
            font.pointSize: fp(12)
        }
    }
}
