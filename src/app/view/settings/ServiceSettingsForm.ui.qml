import QtQuick 2.4
import "../components"

MenuPage {
    property variant service: QtObject {}

    title: service.name

    menuItems: [
        MenuItem {
            //% "general"
            text: qsTrId("settings.general")
            onClicked: stack.push(Qt.createComponent("SettingsList.qml"), {
                settings: service.settings
            })
        }
    ]
}
