import QtQuick 2.4
import "controls"

StackView {
    id: control

    property real lineHeight: 40

    initialItem: content

    Content {
        id: content

        lineHeight: control.lineHeight
    }
}
