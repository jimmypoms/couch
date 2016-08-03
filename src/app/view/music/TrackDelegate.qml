import QtQuick 2.2

Item {
    property var item: ({})

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

    Text {
        anchors.fill: parent
        text: item.name
        color: "white"
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
