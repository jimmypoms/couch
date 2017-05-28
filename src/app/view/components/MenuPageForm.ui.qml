import QtQuick 2.4
import QtQuick.Controls.Material 2.0

import "../controls"

FocusScope {
    id: component

    property int contentMargin: 16
    property alias title: title.text
    property alias description: description.text
    property alias additionalDescription: additionalDescription.text
    property alias contentPange: contentPane
    property alias actionsPane: actionsPane
    property variant content: Item {}

    Pane {
        id: contentPane

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        padding: 3 * contentMargin

        width: 2 * parent.width / 3

        Column {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            spacing: 16

            HugeLabel {
                id: title
                elide: Text.ElideRight
                width: parent.width
            }
            LargeLabel {
                id: description
                secondary: true
                elide: Text.ElideRight
                width: parent.width
            }
            MediumLabel {
                id: additionalDescription
                secondary: true
                wrapMode: Text.Wrap
                width: parent.width
            }
        }
    }

    Pane {
        id: actionsPane

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: contentPane.right
        anchors.bottom: parent.bottom

        focus: true
        padding: 0

        contentItem.children: [
            content
        ]
    }
}
