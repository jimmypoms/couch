import QtQuick 2.4

import "../controls"

ListView {
    id: list

    property real lineHeight: 40
    property bool focused: list.focus
    property color color: list.focused ? highlightColor : "grey"
    property color highlightColor: "green"
    property int highlightHeight: list.focused ? 5 : 2
    property string emptyText: qsTr("list.empty")
    property bool loading: model ? !!model.loading : false

    spacing: 20
    flickableDirection: Flickable.HorizontalFlick
    orientation: ListView.Horizontal

    highlightMoveDuration: 200
    highlightResizeDuration: 200
    highlightFollowsCurrentItem: true
    highlightRangeMode: ListView.StrictlyEnforceRange
    preferredHighlightBegin: 0
    preferredHighlightEnd: 96

    highlight: Item {
        z: 2
        Rectangle {
            height: list.highlightHeight
            anchors.left: parent.left
            anchors.right: parent.right
            y: list.lineHeight * 4
            color: list.color
        }
    }

    delegate: ItemListDelegate {
        lineHeight: list.lineHeight
        item: modelData
        viewFocused: list.focused

        Keys.onEnterPressed: {
            itemClicked(modelData);
        }
        Keys.onReturnPressed: {
            itemClicked(modelData);
        }
    }

    footer: BusyIndicator {
        id: busyIndicator

        height: lineHeight * 4
        visible: loading
    }

    MediumLabel {
        id: emptyLabel

        anchors.centerIn: parent
        text: emptyText
        visible: false

        Rectangle {
            anchors.topMargin: 5
            anchors.top: emptyLabel.bottom
            anchors.left: emptyLabel.left
            anchors.right: emptyLabel.right
            height: 5
            color: "green"
            visible: list.focused
        }
    }

    states: [
        State {
            name: "empty"
            when: !list.model || list.model.length === 0
            PropertyChanges {
                target: emptyLabel
                visible: true
            }
        }
    ]
}
