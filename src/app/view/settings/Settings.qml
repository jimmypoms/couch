import QtQuick 2.4
import "../components"

SettingsForm {
    id: component

    property variant services: couch.services

    Repeater {
        id: repeater

        visible: false
        model: services
        delegate: MenuItem {
            text: modelData.name
            onClicked: stack.push(Qt.createComponent("ServiceSettings.qml"), {
                service: modelData
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
