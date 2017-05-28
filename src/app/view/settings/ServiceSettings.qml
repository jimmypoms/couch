import QtQuick 2.4
import "../components"

ServiceSettingsForm {
    id: component

    Repeater {
        id: repeater

        visible: false
        model: service.providers
        delegate: MenuItem {
            id: providerSettings

            text: modelData.name
            //% "Configure aspects of the %1 provider"
            description: qsTrId("settings.provider.description").arg(modelData.name)
            onClicked: stack.push(Qt.createComponent("SettingsList.qml"), {
                title: providerSettings.text,
                description: providerSettings.description,
                settingList: component.settingList.settingList(modelData)
            })
        }

        onItemAdded: {
            component.model.append(item)
        }
    }
}
