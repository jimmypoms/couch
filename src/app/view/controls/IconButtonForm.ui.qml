import QtQuick 2.4
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

Button {
    id: control

    property alias source: icon.source
    property alias iconSize: icon.iconSize

    padding: iconSize / 2
    topPadding: padding
    bottomPadding: padding
    leftPadding: padding
    rightPadding: padding

    contentItem: Icon {
        id: icon

        topPadding: control.topPadding
        bottomPadding: control.bottomPadding
        leftPadding: control.leftPadding
        rightPadding: control.rightPadding

        color: !control.enabled ? control.Material.hintTextColor :
                control.flat && control.highlighted ? control.Material.accentColor :
                control.highlighted ? control.Material.primaryHighlightedTextColor : control.Material.primaryTextColor
    }

    background.width: icon.width
    background.height: icon.height
    background.implicitHeight: control.contentItem.implicitHeight
    background.implicitWidth: control.contentItem.implicitWidth
    background.x: control.leftPadding
    background.y: control.topPadding
}
