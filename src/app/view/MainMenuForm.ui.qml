import QtQuick 2.4
import "components"
import "controls"
import "settings"

MenuPage {
    id: mainMenu

    menuItems: [
        MenuItem {
            text: qsTr("back to couch")
            onClicked: stack.push(main)
        },
        MenuItem {
            text: qsTr("configure")
            onClicked: stack.push(settings)
        },
        MenuItem {
            text: qsTr("exit")
            onClicked: Qt.quit()
        }
    ]
}
