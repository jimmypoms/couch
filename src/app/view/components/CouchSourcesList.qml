import QtQuick 2.2

import org.couch.sourcelist 1.0

import "../components"

Item {
    property alias sourceList: list.model
    property alias name: button.text
    property bool loading: false

    visible: list.model ? list.model.length !== 0 : false

    ListView {
        id: list
        focus: true

        anchors.top: parent.top
        anchors.bottom: button.top
        anchors.right: parent.right
        anchors.left: parent.left

        verticalLayoutDirection: ListView.BottomToTop
        delegate: CouchButton {
            height: dp(30)
            fontPointSize: fp(7)
            fontWeight: Font.Light
            width: button.width
            text: modelData.quality

            onClicked: {
                player.play(modelData);
            }
        }
    }

    CouchButton {
        id: button
        focus: false
        enabled: false

        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        height: dp(50)

        color: "orange"
    }
}

