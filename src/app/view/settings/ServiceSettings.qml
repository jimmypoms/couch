import QtQuick 2.4
import "../components"

ServiceSettingsForm {
    id: component

    property variant providers: service.providers

    Repeater {
        id: repeater

        visible: false
        model: providers
        delegate: MenuItem {
            text: modelData.name
            onClicked: stack.push(Qt.createComponent("ProviderSettings.qml"), {
                provider: modelData
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
