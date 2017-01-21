import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

TabBar {
    id: control

    property TabView tabView: TabView {}

    states: [
        State {
            name: "unfocused"
            when: !control.activeFocus
            PropertyChanges {
                target: control
                Material.accent: Material.foreground
            }
        }
    ]
}
