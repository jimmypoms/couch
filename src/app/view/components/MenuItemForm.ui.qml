import QtQuick 2.4
import QtQuick.Controls.Material 2.0

import "../controls"

ItemDelegate {
    id: control

    highlighted: ListView.isCurrentItem
    width: ListView.view ? ListView.view.width : implicitWidth

    property alias description: description.text

    contentItem: Item {
        anchors.leftMargin: control.checkable && !control.mirrored ? (control.indicator ? control.indicator.width : 0) + control.spacing : 0
        anchors.rightMargin: control.checkable && control.mirrored ? (control.indicator ? control.indicator.width : 0) + control.spacing : 0

        implicitHeight: title.implicitHeight + description.implicitHeight

        Text {
            id: title

            anchors.top: parent.top

            text: control.text
            font: control.font
            color: control.enabled ? control.Material.primaryTextColor : control.Material.hintTextColor
            elide: Text.ElideRight
            visible: control.text
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: description

            anchors.top: title.bottom

            font: control.font
            color: control.enabled ? control.Material.secondaryTextColor : control.Material.hintTextColor
            elide: Text.ElideRight
            visible: control.text
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }
}
