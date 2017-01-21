import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import Couch 1.0

import "components"
import "controls"
import "music"

FocusScope {
    id: content

    property int contentMargin: 32
    property alias tabBar: contentTabBar
    property alias tabView: contentTabView
    property alias flickable: flickable
    property alias overlay: overlay

    Rectangle {
        id: overlay

        anchors.fill: parent

        color: Material.foreground
        opacity: searchBar.active ? 0.5 : 0
    }

    Flickable {
        id: flickable

        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        contentHeight: contentTabBar.anchors.topMargin + contentTabBar.height + contentTabView.height

        SearchBar {
            id: searchBar

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            padding: 16

            KeyNavigation.down: activeSearch ? contentTabView : contentTabBar
        }

        TabBar {
            id: contentTabBar

            anchors.top: searchBar.bottom
            anchors.left: parent.left
            anchors.topMargin: 104
            anchors.leftMargin: content.contentMargin

            focus: true
            currentIndex: 0
            tabView: contentTabView

            KeyNavigation.up: searchBar

            TabButton {
                text: qsTr("Music")
            }
        }

        TabView {
            id: contentTabView

            anchors.top: contentTabBar.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: content.contentMargin
            anchors.rightMargin: content.contentMargin
            anchors.leftMargin: content.contentMargin

            SearchContainer {
                service: music
                searchBar: searchBar
                filter: MusicFilter {
                    order: MusicFilter.Popular
                }
                searchResult: SearchResult {
                    emptyText: qsTr("type to search music")
                }
                content: Music {
                }
            }
        }
    }
}

