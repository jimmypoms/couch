import QtQuick 2.2

import "../components"

Item {
    id: itemContainer

    property var item: {}
    property string placeholder: ''
    property color containerColor: '#383F42'

    z: activeFocus ? 2 : 1
    signal clicked(var item)

    Keys.onEnterPressed: {
        clicked(item);
    }
    Keys.onReturnPressed: {
        clicked(item);
    }

    Rectangle {
        id: content
        color: "transparent"
        antialiasing: true
        anchors.fill: parent
        anchors.margins: dp(5)
        radius: 5

        CouchPlaceholderImage {
            id: previewImage
            anchors.fill: parent
            source: itemContainer.item.metadata ? itemContainer.item.metadata.image : ''
            placeholder: itemContainer.placeholder
            smooth: true
        }

        Rectangle {
            id: labelContainer
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            height: Math.min(parent.height * 0.35, dp(100))
            color: '#383F42'
        }

        Rectangle {
            anchors.fill: labelContainer
            color: itemContainer.containerColor
            opacity: itemContainer.activeFocus ? 0.5 : 0

            Behavior on opacity {
                NumberAnimation {
                    duration: 200
                }
            }
        }

        Text {
            text: itemContainer.item.title
            color: "white"
            font.weight: Font.Light
            font.pointSize: labelContainer.height ? labelContainer.height * 0.11 : fp(10)

            anchors.top: labelContainer.top
            anchors.left: labelContainer.left
            anchors.right: labelContainer.right
            anchors.bottom: labelContainer.bottom
            anchors.margins: labelContainer.height * 0.07

            wrapMode: Text.WordWrap
            elide: Text.ElideRight
        }

        Rectangle {
            id: curtain
            anchors.fill: parent
            color: "black"
            opacity: itemContainer.activeFocus ? 0 : 0.3

            Behavior on opacity {
                NumberAnimation {
                    duration: 200
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
        onClicked: {
            itemContainer.clicked(itemContainer.item);
        }
    }

    states: State {
        name: "active"; when: itemContainer.activeFocus
        PropertyChanges { target: content; scale: 1.15 }
    }

    transitions: Transition {
        NumberAnimation { property: "scale"; duration: 200; easing.type: Easing.OutBack }
    }

}
