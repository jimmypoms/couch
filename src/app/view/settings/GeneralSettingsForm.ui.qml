import QtQuick 2.4
import QtQuick.Layouts 1.3

import "../controls"

SubSettings {
    property alias tabBar: generalSettingsTabBar
    property alias tabView: generalSettingsTabView

    TabBar {
        id: generalSettingsTabBar

        focus: true
        currentIndex: 0
        tabView: generalSettingsTabView

        TabButton {
            text: qsTr("Appearence")
            font.pointSize: 12
            font.weight: Font.Light
        }
    }

    TabView {
        id: generalSettingsTabView

        Layout.fillWidth: true
        Layout.fillHeight: true

        SettingsList {
        }
    }
}
