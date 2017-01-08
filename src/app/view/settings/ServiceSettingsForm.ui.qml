import QtQuick 2.4
import QtQuick.Layouts 1.3

import "../controls"

SubSettings {
    property variant service: QtObject {}
    property variant providers: service.providers

    property alias tabBar: serviceSettingsTabBar
    property alias tabView: serviceSettingsTabView

    TabBar {
        id: serviceSettingsTabBar

        focus: true
        anchors.left: parent.left
        currentIndex: 0
        tabView: serviceSettingsTabView

        TabButton {
            text: qsTr("General")
            font.pointSize: 12
            font.weight: Font.Light
        }

        Repeater {
            model: providers
            delegate: TabButton {
                text: modelData.name
                font.pointSize: 12
                font.weight: Font.Light
            }
        }
    }

    TabView {
        id: serviceSettingsTabView

        Layout.fillWidth: true
        Layout.fillHeight: true

        SettingsList {
            settings: service.settings
        }

        Repeater {
            model: providers
            delegate: ProviderSettings {
                provider: modelData
            }
        }
    }
}
