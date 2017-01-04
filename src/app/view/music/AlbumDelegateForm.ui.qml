import QtQuick 2.5
import Couch 1.0

import "../controls"
import "../components"

FocusScope {
    id: component

    property ListView list: null
    property bool viewFocused: false
    property int lineHeight: 50
    property variant album: Album {}

    property alias albumDelegate: albumDelegate
    property alias trackLabel: trackLabel
    property alias trackList: trackList

    width: albumDelegate.width

    ItemListDelegate {
        id: albumDelegate

        focus: true
        lineHeight: component.lineHeight
        item: album
        viewFocused: component.viewFocused
        focused: parent.activeFocus && viewFocused

        KeyNavigation.down: trackList
    }

    MediumLabel {
        id: trackLabel

        text: qsTr("Tracks")
        height: component.lineHeight
        visible: albumDelegate.viewFocused

        anchors.top: albumDelegate.bottom
    }

    ListView {
        id: trackList

        clip: true
        model: album.tracks
        height: mainFlickable.height - (component.lineHeight * 5)
        visible: albumDelegate.viewFocused
        orientation: ListView.Vertical
        highlightMoveDuration: 200
        highlightResizeDuration: 0
        highlightFollowsCurrentItem: true
        highlightRangeMode: ListView.ApplyRange
        preferredHighlightBegin: component.lineHeight
        preferredHighlightEnd: trackList.height - component.lineHeight

        anchors.top: trackLabel.bottom

        KeyNavigation.up: albumDelegate

        delegate: TrackDelegate {
            track: modelData
            height: component.lineHeight
            width: trackList.width
        }

        highlight: Rectangle {
            color: trackList.activeFocus ? "grey" : "transparent"
        }
    }
}
