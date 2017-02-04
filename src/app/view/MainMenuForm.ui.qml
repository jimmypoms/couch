import QtQuick 2.4
import "components"
import "controls"
import "settings"

MenuPage {
    id: mainMenu

    menuItems: [
        MenuItem {
            //% "back to couch"
            text: qsTrId("couch.back")
            onClicked: stack.push(main)
        },
        MenuItem {
            //% "configure"
            text: qsTrId("couch.configure")
            onClicked: stack.push(settings)
        },
        MenuItem {
            //% "exit"
            text: qsTrId("couch.exit")
            onClicked: Qt.quit()
        }
    ]
}
