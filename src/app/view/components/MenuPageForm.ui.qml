import QtQuick 2.4
import QtQuick.Controls.Material 2.0

import "../controls"

Flickable {
    id: component

    property alias title: title.text
    property alias description: description.text
    property alias actions: actions.data

    Rectangle {
        id: contentSection

        anchors.fill: parent

        color: Material.background

        Column {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            HugeLabel {
                id: title
            }
            LargeLabel {
                id: description
                secondary: true
            }
        }
    }

    Rectangle {
        id: actionsSection

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        width: parent.width / 3
        color: Material.primary

        Column {
            id: actions

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            focus: true
        }
    }
}
