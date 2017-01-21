import QtQuick 2.4
import QtQuick.Layouts 1.3

import "../controls"
import ".."

Detail {
    id: content

    property variant services: couch.services

    title: qsTr("Settings")
    spacing: 0

    Item {
        height: 144
    }

    TabBar {
        id: settingsTabBar

        focus: true
        anchors.left: parent.left
        currentIndex: 0
        tabView: settingsTabView
        contentItem.implicitHeight: 35

        TabButton {
            text: qsTr("General")
            font.pointSize: 12
        }

        Repeater {
            model: services
            delegate: TabButton {
                text: modelData.name
                font.pointSize: 12
            }
        }
    }

    TabView {
        id: settingsTabView

        Layout.fillWidth: true
        Layout.fillHeight: true

        GeneralSettings {
        }

        Repeater {
            model: services
            delegate: ServiceSettings {
                service: modelData
            }
        }
    }
}
