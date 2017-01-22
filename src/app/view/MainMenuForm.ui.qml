import QtQuick 2.4
import "components"
import "controls"

MenuPage {
    id: mainMenu

    actions: [
        Button {
            text: qsTr("back to couch")
            onClicked: stack.push(main)
        },
        Button {
            text: qsTr("configure")
        },
        Button {
            text: qsTr("exit")
            onClicked: Qt.quit()
        }
    ]
}
