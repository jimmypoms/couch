import QtQuick 2.4
import "../components"

SettingsListForm {
    id: component

    Repeater {
        id: repeater

        visible: false
        model: component.settingList
        delegate: MenuItem {
            text: modelData.title
            description: modelData.value
            onClicked: {
                stack.push(Qt.createComponent("FolderSetting.qml"), {
                    title: modelData.title,
                    setting: modelData,
                })
            }
        }

        onItemAdded: {
            component.model.append(item)
        }
    }
}
