import QtQuick 2.4
import "../controls"

Item {
    id: control

    property variant settings: QtObject {}
    property bool focused: control.focus
    property string emptyText: qsTr("settings.empty")

    MediumLabel {
        id: emptyLabel

        anchors.centerIn: parent
        text: emptyText
        visible: false

        Rectangle {
            anchors.topMargin: 5
            anchors.top: emptyLabel.bottom
            anchors.left: emptyLabel.left
            anchors.right: emptyLabel.right
            height: 5
            color: "green"
            visible: control.focused
        }
    }

    states: [
        State {
            name: "empty"
            when: !settings || !settings.length
            PropertyChanges {
                target: emptyLabel
                visible: true
            }
        }
    ]
}
