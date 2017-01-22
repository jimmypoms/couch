import QtQuick 2.7
import QtQuick.Layouts 1.3

import Couch 1.0

import ".."
import "../controls"
import "../components"

Master {
    id: music

    property alias featuredLabel: featuredLabel
    property alias featuredList: featuredList
    property alias genreTabView: genreTabView
    property alias genreTabViewRepeater: genreTabViewRepeater
    property alias genreList: genreList

    MediumLabel {
        id: featuredLabel

        text: qsTr("Featured")
    }
    ItemListView {
        id: featuredList

        Layout.fillWidth: true

        KeyNavigation.down: genreList
    }

    TabBar {
        id: genreTabView

        Repeater {
            id: genreTabViewRepeater
            delegate: TabButton {
                text: name
                secondary: true
            }
        }

        KeyNavigation.up: featuredList
        KeyNavigation.down: genreList
    }
    ItemListView {
        id: genreList

        Layout.fillWidth: true

        KeyNavigation.up: genreTabView
    }
}
