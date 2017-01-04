import QtQuick 2.7
import QtQuick.Layouts 1.3

import Couch 1.0

import "../controls"
import "../components"

Item {
    property real lineHeight: 50
    property real listHeight: lineHeight * 6

    property int spacing: 20
    property bool searchVisible: false
    property alias search: search
    property alias searchField: search.input
    property alias searchList: search.list
    property alias featuredList: musicFeaturedList
    property alias genreComboBox: musicGenreComboBox
    property alias genreList: musicGenreList
    property alias historyList: musicHistoryList

    id: music

    anchors.fill: parent
    implicitHeight: searchVisible ? search.implicitHeight + list.implicitHeight : list.implicitHeight

    ItemSearchView {
        id: search

        anchors.topMargin: music.spacing
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        spacing: music.spacing
        searchVisible: music.searchVisible
        lineHeight: music.lineHeight
        listHeight: music.listHeight
    }

    ColumnLayout {
        id: list

        anchors.topMargin: music.spacing
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        spacing: music.spacing
        MediumLabel {
            text: qsTr("Featured")
            Layout.preferredHeight: music.lineHeight
            verticalAlignment: Text.AlignBottom
        }
        ItemListView {
            id: musicFeaturedList

            Layout.fillWidth: true
            height: music.listHeight

            KeyNavigation.up: searchVisible ? search.list : null
            KeyNavigation.down: musicGenreList
        }

        ComboBox {
            id: musicGenreComboBox
            Layout.preferredHeight: music.lineHeight
            leftPadding: 0
            rightPadding: 0

            KeyNavigation.up: musicFeaturedList
            KeyNavigation.down: musicGenreList
        }

        ItemListView {
            id: musicGenreList

            Layout.fillWidth: true
            height: music.listHeight

            KeyNavigation.up: musicGenreComboBox
            KeyNavigation.down: musicHistoryList
        }

        MediumLabel {
            text: qsTr("History")
            Layout.preferredHeight: music.lineHeight
            verticalAlignment: Text.AlignBottom
        }
        ItemListView {
            id: musicHistoryList

            Layout.fillWidth: true
            height: music.listHeight

            KeyNavigation.up: musicGenreList
        }
    }

    states: [
        State {
            name: "searchVisible"
            when: searchVisible
            AnchorChanges {
                target: list
                anchors.top: search.bottom
            }
        }
    ]
}
