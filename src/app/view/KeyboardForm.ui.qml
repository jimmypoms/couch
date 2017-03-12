import QtQuick 2.4
import QtQuick.Controls.Material 2.0
import QtQuick.VirtualKeyboard 2.1

Rectangle {
    id: component

    readonly property int maxHeight: 250
    property alias inputPanel: inputPanel

    height: state === "visible" ? maxHeight : 0
    color: Material.primary

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
