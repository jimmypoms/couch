import QtQuick 2.0

Item {
    id: notifications
    enabled: false

    ListModel {
        id: notificationsModel
    }

    ListView {
        id: notificationsView
        anchors.fill: parent

        model: notificationsModel
        delegate: Item {
            width: parent.width
            height: dp(60)
            Rectangle {
                id: warningBox
                anchors.margins: dp(5)
                anchors.fill: parent
                radius: dp(10)
                color: boxColor
            }
            Text {
                anchors.centerIn: parent
                anchors.left: parent.left
                anchors.right: parent.right
                color: "white"
                wrapMode: Text.WordWrap
                text: message
                font.weight: Font.Light
                font.pointSize: fp(10)
            }
        }
        add: Transition {
            NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 500; easing.type: Easing.InOutQuad }
            NumberAnimation { property: "y"; from: -dp(60); duration: 500; easing.type: Easing.InOutQuad }
        }
        addDisplaced: Transition {
            NumberAnimation { properties: "y"; duration: 500; easing.type: Easing.InOutQuad }
        }
        remove: Transition {
            NumberAnimation { property: "opacity"; to: 0; duration: 500; easing.type: Easing.InOutQuad }
            NumberAnimation { properties: "y"; to: -dp(60); duration: 500; easing.type: Easing.InOutQuad }
        }
    }

    Timer {
        id: timer
        interval: 3000
        onTriggered: {
            notificationsModel.clear();
        }
    }

    function warning(message) {
        notificationsModel.insert(0, {
            "message": message,
            "boxColor": "yellow"
        });
        timer.restart()
    }

    function error(message) {
        notificationsModel.insert(0, {
            "message": message,
            "boxColor": "red"
        });
        timer.restart()
    }

    function clear() {
        notificationsModel.clear()
    }
}
