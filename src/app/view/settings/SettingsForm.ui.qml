import QtQuick 2.4
import "../components"

MenuPage {
    id: component

    property variant services: couch.services
    property variant settingsList: settings

    //% "Settings"
    title: qsTrId("settings.couch")
    //% "Configure aspects of the application"
    description: qsTrId("settings.couch.description")

    menuItems: [
        MenuItem {
            id: couchSettings

            //% "Couch settings"
            text: qsTrId("settings.couch.general")
            //% "Configure general aspects of couch"
            description: qsTrId("settings.couch.general.description")
            onClicked: stack.push(Qt.createComponent("SettingsList.qml"), {
                title: couchSettings.text,
                description: couchSettings.description,
                settingList: component.settingsList
            })
        }
    ]
}
