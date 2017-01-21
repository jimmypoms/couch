import QtQuick 2.4
import QtQuick.Layouts 1.3

import "components"

FocusScope {
    id: header

    property bool playing: false
    property alias playback: playback
    property int contentMargin: 8

    opacity: playing ? 1 : 0

    RowLayout {
        anchors.bottom: header.top
        anchors.left: header.left
        anchors.right: header.right
        anchors.leftMargin: contentMargin
        anchors.rightMargin: contentMargin
        anchors.bottomMargin: contentMargin

        PlaybackInfo {
            currentItem: player.currentItem
            Layout.alignment: Qt.AlignLeft
        }
        PlaybackActions {
            Layout.alignment: Qt.AlignRight
        }
    }

    PlaybackControls {
        id: playback

        height: 0
        opacity: 0

        anchors.fill: parent
    }

    states: [
        State {
            name: "playback"
            when: header.playing
            PropertyChanges {
                target: playback
                focus: true
                opacity: 1
            }
        }
    ]
}
