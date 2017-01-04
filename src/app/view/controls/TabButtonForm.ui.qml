import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.TabButton {
    id: control

    text: ""

    property color color: "grey"
    property color checkedColor: "white"
    property color highlightColor: "green"

    topPadding: 10
    bottomPadding: 10
    rightPadding: 10
    font.pointSize: 16

    width: implicitWidth + leftPadding + rightPadding
    height: implicitHeight + topPadding + bottomPadding
    implicitWidth: contentItem.implicitWidth
    implicitHeight: contentItem.implicitHeight

    contentItem: Row {
        anchors.left: parent.left
        spacing: 5

        Text {
            id: text
            text: control.text
            font: control.font
            elide: Text.ElideRight
            color: control.color
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: Item {
    }

    states: [
        State {
            name: "checked"
            when: control.checked
            PropertyChanges {
                target: control
                color: control.checkedColor
            }
        },
        State {
            name: "focused"
            when: control.focus
            PropertyChanges {
                target: control
                color: control.highlightColor
            }
        }
    ]
}
