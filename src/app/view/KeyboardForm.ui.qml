import QtQuick 2.4
import QtQuick.VirtualKeyboard 2.1

Item {
    id: component

    readonly property int maxHeight: 250
    property alias inputPanel: inputPanel

    height: state === "visible" ? maxHeight : 0

    InputPanel {
        id: inputPanel

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        width: 750
    }

    states: [
        State {
            name: "visible"
            when: Qt.inputMethod.visible
            PropertyChanges {
                target: component
                height: component.maxHeight
            }
        }
    ]
}
