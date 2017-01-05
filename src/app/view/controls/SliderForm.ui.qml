import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.Slider {
    id: control

    padding: 6
    stepSize: (to - from) / 15

    handle: Rectangle {
        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
        y: control.topPadding + (control.availableHeight - height) / 2
    }

    background: Rectangle {
        x: control.leftPadding + (horizontal ? 0 : (control.availableWidth - width) / 2)
        y: control.topPadding + (horizontal ? (control.availableHeight - height) / 2 : 0)
        implicitWidth: horizontal ? 200 : control.width
        implicitHeight: horizontal ? control.height : 200
        width: horizontal ? control.availableWidth : 1
        height: horizontal ? 1 : control.availableHeight
        color: "transparent"
        scale: horizontal && control.mirrored ? -1 : 1

        readonly property bool horizontal: control.orientation === Qt.Horizontal

        Rectangle {
            x: parent.horizontal ? 0 : (parent.width - width) / 2
            y: parent.horizontal ? (parent.height - height) / 2 : control.visualPosition * parent.height
            width: parent.horizontal ? control.position * parent.width : control.width
            height: parent.horizontal ? control.height : control.position * parent.height

            color: "lightseagreen"
        }
    }
}
