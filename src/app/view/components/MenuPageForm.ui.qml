import QtQuick 2.4
import QtQuick.Controls.Material 2.0

import "../controls"

FocusScope {
    id: component

    property int contentMargin: 16
    property alias title: title.text
    property alias description: description.text
    property alias menuItems: actionsModel.children
    property alias contentPange: contentPane
    property alias actionsPane: actionsPane

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
            }
            LargeLabel {
                id: description
                secondary: true
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

        ListView {
            id: actions

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            displayMarginBeginning: actionsPane.height / 2
            displayMarginEnd: actionsPane.height / 2

            focus: true
            model: VisualItemModel {
                id: actionsModel
            }
        }
    }
}
