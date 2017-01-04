import QtQuick 2.4

FocusScope {
    id: header

    property bool playing: false
    property alias header: headerMenu
    property alias playback: playback
    property int contentMargin: 0

    HeaderMenu {
        id: headerMenu

        focus: true
        contentMargin: header.contentMargin

        anchors.fill: parent
        KeyNavigation.down: header.KeyNavigation.down
    }

    PlaybackControls {
        id: playback

        visible: false
        contentMargin: mainFlickable.contentMargin

        anchors.fill: parent
    }

    states: [
        State {
            name: "playback"
            when: header.playing
            PropertyChanges {
                target: headerMenu
                visible: false
                focus: false
            }
            PropertyChanges {
                target: playback
                visible: true
                focus: true
            }
        }
    ]
}
