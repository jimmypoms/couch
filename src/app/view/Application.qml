import QtQuick 2.4
import "components"
import "controls"
import "settings"

ApplicationWindow {
    visible: true
    visibility: "FullScreen"

    StackView {
        id: stack

        anchors.fill: parent

        initialItem: mainMenu

        Settings {
            id: settingsMenu

            visible: false
        }
        MainMenu {
            id: mainMenu

            visible: false
        }
        Main {
            id: main
        }
    }

    Loader {
        source: "Keyboard.qml"

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }

    Component.onCompleted: {
        stack.push(main);
    }
}
