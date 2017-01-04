import QtQuick 2.4
import Couch 1.0

Item {
    id: component

    property bool searchVisible: true
    property real lineHeight: 50
    property real listHeight: lineHeight * 5
    property int spacing: 20

    property alias input: searchField
    property alias list: searchList

    property Filter filter: null
    property variant service: null

    clip: true
    opacity: searchVisible ? 1 : 0
    height: searchField.height + music.listHeight + searchList.spacing

    SearchField {
        id: searchField

        anchors.top: parent.top
        anchors.left: parent.left
        height: lineHeight

        leftPadding: 0
        rightPadding: 0
        keyboardHeight: 70
        keyboardWidth: parent.width

        KeyNavigation.down: searchList
    }
    Item {
        id: spacing

        anchors.top: searchField.bottom
        height: component.spacing
    }
    Item {
        id: keyboardSpacing

        anchors.top: searchField.bottom
        height: searchField.keyboardHeight
    }
    ItemListView {
        id: searchList

        height: listHeight
        anchors.top: spacing.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        KeyNavigation.up: searchField
    }

    states: [
        State {
            name: "searchVisible"
            when: searchField.keyboardVisible
            AnchorChanges {
                target: searchList
                anchors.top: keyboardSpacing.bottom
            }
        }
    ]
}
