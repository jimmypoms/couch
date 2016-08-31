import QtQuick 2.2
import QtQuick.Layouts 1.2

import "../components"

FocusScope {
    id: itemContainer
    focus: true

    property var item: ({})
    property color containerColor: '#383F42'

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            if (itemContainer.GridView.view) {
                itemContainer.GridView.view.currentIndex = index;
            } else {
                itemContainer.ListView.view.currentIndex = index;
            }
            itemContainer.forceActiveFocus()
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "grey"
        opacity: parent.activeFocus ? 0.3 : 0

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }

    FocusScope {
        id: header
        width: parent.width
        height: dp(200)
        focus: true

        Keys.onDownPressed: {
            trackList.forceActiveFocus();
        }

        CouchPlaceholderImage {
            id: cover
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            height: parent.height
            width: parent.height

            source: item.cover
            placeholder: "../images/placeholder-album.svg"
        }

        Text {
            anchors.margins: dp(5)
            anchors.left: cover.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: playButton.top
            color: "white"
            font.weight: Font.Light
            font.pointSize: fp(12)

            text: item.name
            wrapMode: Text.WordWrap
            elide: Text.ElideRight
        }

        CouchButton {
            id: playButton
            anchors.leftMargin: dp(5)
            anchors.right: parent.right
            anchors.left: cover.right
            anchors.bottom: parent.bottom
            text: "play all"
            focus: true

            Layout.alignment: Qt.AlignBottom | Qt.AlignLeft
            height: dp(50)

            color: "orange"
            onClicked: {
            }
        }
    }

    CouchListView {
        id: trackList
        clip: true

        Keys.onUpPressed: {
            header.forceActiveFocus();
        }

        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        orientation: ListView.Vertical

        items: item.tracksSortedByTrackPosition()
        loading: items.loading
        delegate: TrackDelegate {
            height: dp(50)
            width: parent.width
            item: modelData
        }
    }
}
