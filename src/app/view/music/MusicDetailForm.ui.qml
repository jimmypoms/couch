import QtQuick 2.4
import QtQuick.Layouts 1.3
import Couch 1.0

import ".."
import "../controls"
import "../components"

Detail {
    id: component

    property variant artist: Artist {}
    property alias playAllButton: playAllButton
    property alias actions: actions
    property alias albums: albums

    title: artist.name
    image: artist.cover ? artist.cover : (artist.metadata ? artist.metadata.image : "")

    MediumLabel {
        text: ""
    }

    FocusScope {
        id: actions

        focus: true
        height: actionsRow.height + 72
        Layout.fillWidth: true

        KeyNavigation.down: albums

        RowLayout {
            id: actionsRow

            ItemListDelegate {
                id: playAllButton

                focus: true
                focused: playAllButton.activeFocus
                item: component.artist
                //% "play all"
                name: qsTrId("couch.playall")

                Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            }

            ListView {
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            }
        }
    }

    MediumLabel {
        //% "Albums"
        text: qsTrId("music.albums")
    }

    ItemListView {
        id: albums

        Layout.fillWidth: true
        model: artist.albums

        KeyNavigation.up: actions
    }
}
