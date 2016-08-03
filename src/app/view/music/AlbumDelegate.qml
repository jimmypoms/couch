import QtQuick 2.2
import QtQuick.Layouts 1.2

import "../components"

Item {
    id: itemContainer

    property var item: ({})
    property color containerColor: '#383F42'

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

    Item {
        id: header
        width: parent.width
        height: dp(100)

        CouchPlaceholderImage {
            anchors.fill: parent

            source: item.cover
            placeholder: "../images/placeholder-album.svg"
        }

        Rectangle {
            id: curtain
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: dp(50)
            color: "black"
            opacity: 0.7
        }

        Text {
            anchors.leftMargin: dp(5)
            anchors.left: curtain.left
            anchors.verticalCenter: curtain.verticalCenter
            color: "white"
            font.weight: Font.Light
            font.pointSize: fp(10)

            text: item.name
        }
    }

    CouchListView {
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        orientation: ListView.Vertical

        items: item.tracks
        loading: items.loading
        delegate: TrackDelegate {
            height: dp(50)
            item: modelData
        }
    }

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
}
