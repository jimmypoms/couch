import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.Slider {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                           (handle ? handle.implicitWidth : 0) + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                            (handle ? handle.implicitHeight : 0) + topPadding + bottomPadding)

    padding: 6

    handle: Rectangle {
        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
        y: control.topPadding + (control.availableHeight - height) / 2
    }

    background: Rectangle {
        x: control.leftPadding + (horizontal ? 0 : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : 0)
        implicitWidth: horizontal ? 200 : 48
        implicitHeight: horizontal ? 48 : 200
        width: horizontal ? control.availableWidth : 1
        height: horizontal ? 1 : control.availableHeight
        color: "transparent"
        scale: horizontal && control.mirrored ? -1 : 1

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        Rectangle {
            x: parent.horizontal ? 0 : (parent.width - width) / 2
            y: parent.horizontal ? (parent.height - height) / 2 : control.visualPosition * parent.height
            width: parent.horizontal ? control.position * parent.width : 3
            height: parent.horizontal ? 3 : control.position * parent.height

            color: "lightseagreen"
        }
    }
}
