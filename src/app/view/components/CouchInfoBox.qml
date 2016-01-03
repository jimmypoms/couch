import QtQuick 2.2
import QtGraphicalEffects 1.0

Item {
    id: root
    property alias text: infotext.text
    property color color: "grey"

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: dp(150)
        height: infotext.height + dp(80)

        border.color: root.color
        border.width: dp(1)

        color: "transparent"

        Image {
            id: icon
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.margins: dp(40)

            sourceSize: Qt.size(dp(80), dp(80))
            source: "../images/icon-info.svg"
        }

        ColorOverlay {
            id: overlay
            anchors.fill: icon
            source: icon
            color: root.color
        }

        Text {
            id: infotext
            anchors.left: icon.right
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: dp(40)

            font.weight: Font.Normal
            font.pointSize: fp(11)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            wrapMode: Text.WordWrap
            color: root.color
        }
    }
}