import QtQuick 2.2

import "../components"

Item {
    id: itemContainer

    signal clicked()

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
            source: modelData.metadata ? modelData.metadata.image : ''
            placeholder: "../images/placeholder-movie.svg"
            smooth: true
        }

        Rectangle {
            id: labelContainer
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            height: parent.height * 0.28
            color: "#383F42"
        }

        Rectangle {
            anchors.fill: labelContainer
            color: "red"
            opacity: itemContainer.activeFocus ? 0.5 : 0

            Behavior on opacity {
                NumberAnimation {
                    duration: 200
                }
            }
        }

        Text {
            text: modelData.title
            color: "white"
            font.weight: Font.Light
            font.pointSize: fp(12)

            anchors.top: labelContainer.top
            anchors.left: labelContainer.left
            anchors.right: labelContainer.right
            anchors.bottom: labelContainer.bottom
            anchors.margins: dp(15)

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
            itemContainer.clicked();
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
