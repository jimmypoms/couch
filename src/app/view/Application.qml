import QtQuick 2.4
import "components"
import "controls"

ApplicationWindow {
    visible: true
    visibility: "FullScreen"

    StackView {
        id: stack

        anchors.fill: parent

        initialItem: mainMenu

        MainMenu {
            id: mainMenu
        }
        Main {
            id: main
        }
    }

    Component.onCompleted: {
        stack.push(main);
        main.forceActiveFocus();
    }
}
