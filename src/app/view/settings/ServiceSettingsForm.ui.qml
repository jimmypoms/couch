import QtQuick 2.4
import "../components"

MenuPage {
    id: component

    property variant service: QtObject {}
    property variant settingList: QtObject {}

    title: service.name

    menuItems: [
        MenuItem {
            id: generalSettings
            //% "general"
            text: qsTrId("settings.service.general")
            //% "Configure general settings of the %1 service"
            description: qsTrId("settings.service.general.description").arg(service.name)
            onClicked: stack.push(Qt.createComponent("SettingsList.qml"), {
                title: generalSettings.text,
                description: generalSettings.description,
                settingList: component.settingList
            })
        }
    ]
}
