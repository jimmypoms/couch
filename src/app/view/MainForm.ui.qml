import QtQuick 2.7
import Couch 1.0 as C

Flickable {
    id: mainFlickable

    property color color: "#193441"
    property real lineHeight: 40
    property real contentMargin: 15
    property alias header: header
    property alias content: content

    interactive: false
    boundsBehavior: Flickable.StopAtBounds
    flickableDirection: Flickable.VerticalFlick

    Player {
        anchors.fill: parent
    }

    Rectangle {
        id: contentBackground

        color: mainFlickable.color
        anchors.fill: parent
        opacity: 0.8
    }

    Header {
        id: header

        playing: player.playbackStatus !== C.Player.Stopped
        height: mainFlickable.lineHeight
        contentMargin: mainFlickable.contentMargin

        anchors.left: parent.left
        anchors.right: parent.right

        KeyNavigation.down: content
    }

    ContentStack {
        id: content

        focus: true
        lineHeight: mainFlickable.lineHeight

        anchors.leftMargin: mainFlickable.contentMargin
        anchors.rightMargin: mainFlickable.contentMargin
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: header.bottom
        anchors.topMargin: mainFlickable.contentMargin

        KeyNavigation.up: header
    }
}
