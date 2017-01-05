import QtQuick 2.4
import "components"
import "controls"

FocusScope {
    id: headerMenu

    property alias menuButton: menuButton
    property int contentMargin: 0

    DateTimeLabel {
        anchors.left: parent.left
        anchors.leftMargin: headerMenu.contentMargin
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.top: parent.top
        anchors.bottom: parent.bottom
    }

    DropdownButton {
        id: menuButton

        focus: true
        text: "couch"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        KeyNavigation.down: headerMenu.KeyNavigation.down

        DropdownItem {
            text: "settings"
        }

        DropdownItem {
            text: "close"
            onClicked: Qt.quit()
        }
    }
}
