import QtQuick 2.4
import "../components"

MenuPage {
    id: component

    title: qsTr("Settings")

    menuItems: [
        MenuItem {
            text: qsTr("general")
            onClicked: stack.push(Qt.createComponent("GeneralSettings.qml"))
        }
    ]
}
