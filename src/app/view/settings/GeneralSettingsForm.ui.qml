import QtQuick 2.4
import "../components"

MenuPage {
    title: qsTr("general")

    menuItems: [
        MenuItem {
            text: qsTr("appearence")
            onClicked: stack.push(Qt.createComponent("SettingsList.qml"), {
                settings: couch.settings
            })
        }
    ]
}
