import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

TabButton {
    id: control

    property bool secondary: false

    width: implicitWidth

    contentItem: MediumLabel {
        text: control.secondary ? control.text : control.text.toUpperCase()
        font: control.font
        color: !control.enabled ? control.Material.hintTextColor
                                : control.down || control.checked ? control.Material.accentColor
                                                                  : control.Material.primaryTextColor
        hint: !control.enabled
        secondary: !control.down && !control.checked
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
