import QtQuick 2.4
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

Item {
    id: control

    property alias source: icon.source
    property alias color: overlay.color
    property bool enabled: true
    property real iconSize: 25

    property real padding: 0
    property real topPadding: padding
    property real bottomPadding: padding
    property real leftPadding: padding
    property real rightPadding: padding

    opacity: enabled ? 1 : 0.3
    implicitHeight: icon.implicitHeight + control.topPadding + control.bottomPadding
    implicitWidth: icon.implicitWidth + control.leftPadding + control.rightPadding

    Image {
        id: icon

        anchors.centerIn: parent

        visible: false
        sourceSize.height: iconSize
        sourceSize.width: iconSize
        fillMode: Image.PreserveAspectCrop
    }

    ColorOverlay {
        id: overlay

        anchors.fill: icon

        source: icon
        color: Material.foreground
    }
}
