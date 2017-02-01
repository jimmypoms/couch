import QtQuick 2.4
import "components"
import "controls"

MenuPage {
    id: mainMenu

    title: qsTr("This is a title")
    description: qsTr("this is the description")

    menuItems: [
        MenuItem {
            text: qsTr("back to couch")
            onClicked: stack.push(main)
        },
        MenuItem {
            text: qsTr("configure")
        },
        MenuItem {
            text: qsTr("exit")
            onClicked: Qt.quit()
        }
    ]
}
