import QtQuick 2.4
import "../components"

MenuPage {
    id: component

    //% "Settings"
    title: qsTrId("settings.title")

    menuItems: [
        MenuItem {
            //% "general"
            text: qsTrId("settings.general")
            onClicked: stack.push(Qt.createComponent("GeneralSettings.qml"))
        }
    ]
}
