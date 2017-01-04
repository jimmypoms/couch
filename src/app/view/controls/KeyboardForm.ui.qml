import QtQuick 2.4

Popup {
    id: control

    signal clicked(string character)
    signal backspace()

    width: 1024
    implicitHeight: contentItem.implicitHeight

    background: Rectangle {
        color: "dimgrey"
    }

    contentItem: KeyboardRow {
        id: keyboard
    }
}
