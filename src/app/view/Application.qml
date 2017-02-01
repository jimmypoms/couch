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
            id: settings

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

    Component.onCompleted: {
        stack.push(main);
    }
}
