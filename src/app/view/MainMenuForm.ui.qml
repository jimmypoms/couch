import QtQuick 2.4
import "components"
import "controls"
import "settings"

MenuPageList {
    id: mainMenu

    menuItems: [
        MenuItem {
            //% "back to couch"
            text: qsTrId("couch.back")
            //% "return to couch screen"
            description: qsTrId("couch.back.description")
            onClicked: stack.push(main)
        },
        MenuItem {
            //% "configure"
            text: qsTrId("couch.configure")
            //% "configure couch, services and providers"
            description: qsTrId("couch.configure.description")
            onClicked: stack.push(settingsMenu)
        },
        MenuItem {
            //% "exit"
            text: qsTrId("couch.exit")
            //% "quit couch"
            description: qsTrId("couch.exit.description")
            onClicked: Qt.quit()
        }
    ]
}
