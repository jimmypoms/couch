import QtQuick 2.4
import QtQuick.Controls.Material 2.0

import "../controls"

ListView {
    id: component

    property bool focused: component.activeFocus
    property bool loading: model ? !!model.loading : false
    property alias emptyText: emptyLabel.text

    spacing: 8
    flickableDirection: Flickable.HorizontalFlick
    orientation: ListView.Horizontal
    displayMarginBeginning: 48
    displayMarginEnd: 48
    height: 336

    highlightMoveDuration: 200
    highlightFollowsCurrentItem: true
    highlightRangeMode: ListView.ApplyRange
    preferredHighlightBegin: component.width / 2 - 24
    preferredHighlightEnd: component.width / 2 + 24

    highlight: Item {
    }

    delegate: ItemListDelegate {
        item: modelData
        viewFocused: component.focused

        Keys.onEnterPressed: itemClicked(modelData);
        Keys.onReturnPressed: itemClicked(modelData);
    }

    footer: BusyIndicator {
        id: busyIndicator

        height: 216
        width: 72
        visible: loading
    }

    MediumLabel {
        id: emptyLabel

        anchors.centerIn: parent
        //% "no results"
        text: qsTrId("list.empty")
        visible: false
    }

    states: [
        State {
            name: "empty"
            when: !component.model || component.model.length === 0
            PropertyChanges {
                target: emptyLabel
                visible: true
            }
        }
    ]
}
