import QtQuick 2.7
import QtQuick.Controls.Material 2.0
import Couch 1.0 as C

Flickable {
    id: mainFlickable

    property alias header: header
    property alias content: content

    interactive: false
    boundsBehavior: Flickable.StopAtBounds
    flickableDirection: Flickable.VerticalFlick

    Player {
        color: Material.background
        anchors.fill: parent
    }

    Header {
        id: header

        playing: player.playbackStatus !== C.Player.Stopped
        height: 72
        z: 5

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.top

        KeyNavigation.down: content
    }

    ContentStack {
        id: content

        clip: true
        focus: true

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left

        KeyNavigation.up: header.playing ? header : null
    }
}
