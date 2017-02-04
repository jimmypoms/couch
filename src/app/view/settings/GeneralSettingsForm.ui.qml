import QtQuick 2.4
import "../components"

MenuPage {
    //% "general"
    title: qsTrId("settings.general")

    menuItems: [
        MenuItem {
            //% "appearence"
            text: qsTrId("settings.appearence")
            onClicked: stack.push(Qt.createComponent("SettingsList.qml"), {
                settings: couch.settings
            })
        }
    ]
}
