import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.Button {
    id: control

    property color highlightColor: "green"
    property color color: "white"

    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding
    implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: 10

    contentItem: Text {
        id: text

        text: control.text
        font: control.font
        color: control.color
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
        opacity: control.enabled ? 1 : 0.3
    }

    background: Rectangle {
        id: underline

        anchors.bottom: control.bottom

        height: 2
        color: control.color
        opacity: control.enabled ? 1 : 0.3
    }

    states: [
        State {
            name: "focused"
            when: control.activeFocus
            PropertyChanges {
                target: underline
                height: 5
                color: control.highlightColor
            }
        }
    ]
}
