import QtQuick 2.2
import QtQuick.Layouts 1.2

import "../components"

FocusScope {
    property var item: ({})
    focus: true

    Rectangle {
        anchors.fill: parent
        color: "grey"
        opacity: parent.activeFocus ? 1 : 0

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }

    Item {
        anchors.margins: dp(5)
        anchors.fill: parent
        Text {
            anchors.fill: parent
            font.weight: Font.Light
            font.pointSize: fp(10)
            verticalAlignment: Text.AlignVCenter

            text: (item.metadata.trackPosition ? item.metadata.trackPosition + " - " : "") + item.name
            elide: Text.ElideRight
            color: "white"
        }

        ListView {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            focus: true
            orientation: ListView.Horizontal
            layoutDirection: Qt.RightToLeft

            model: item.providers()
            delegate: CouchIconButton {
                size: dp(40)
                source: "../images/icon-play.svg"

                onClicked: {
                }
            }
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
