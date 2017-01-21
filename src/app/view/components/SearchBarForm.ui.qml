import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import "../controls"

FocusScope {
    id: component

    property int padding: 8
    property int leftPadding: padding
    property int rightPadding: padding
    property int topPadding: padding
    property int bottomPadding: padding

    property bool activeSearch: textField.text.length > 0
    property bool active: textField.activeFocus || activeSearch
    property alias textField: textField
    property alias hintLabel: hintLabel
    property alias text: textField.text

    x: icon.x
    y: icon.y
    implicitHeight: textField.height

    IconButton {
        id: icon

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: leftPadding
        anchors.topMargin: topPadding

        source: "../images/icon-search.svg"
        iconSize: 32
        flat: true

        Material.background: Material.color(Material.Red, Material.Shade700)
        Material.elevation: component.activeFocus ? 8 : 2
    }

    MediumLabel {
        id: hintLabel

        anchors.verticalCenter: icon.verticalCenter
        anchors.left: icon.right

        text: qsTr("search content")
        opacity: component.active ? 0 : hintOpacity
    }

    TextField {
        id: textField

        anchors.verticalCenter: icon.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Material.accent: Material.color(Material.Grey, Material.Shade900)

        focus: true
        padding: 8
        topPadding: 8
        bottomPadding: 8
        width: component.width / 5 * 3
        height: 48
        color: Material.color(Material.Grey, Material.Shade900)
        opacity: component.active ? 1 : 0
        background: Pane {
            Material.background: Material.color(Material.Grey, Material.Shade100)
            Material.elevation: component.activeFocus ? 8 : 2
        }
    }
}
