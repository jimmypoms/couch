import QtQuick 2.4
import "../components"

SettingsForm {
    id: component

    Repeater {
        id: repeater

        visible: false
        model: services
        delegate: MenuItem {
            id: serviceSettings

            text: modelData.name
            //% "Configure aspects of the %1 service"
            description: qsTrId("settings.service.description").arg(modelData.name)
            onClicked: stack.push(Qt.createComponent("ServiceSettings.qml"), {
                service: modelData,
                title: serviceSettings.text,
                description: serviceSettings.description,
                settingList: settings.settingList(modelData)
            })
        }

        onItemAdded: {
            component.list.model.append(item)
        }
    }
    Component.onCompleted: {
        list.currentIndex = 0
    }
}
