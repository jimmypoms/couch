import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

import org.couch.filter.music 1.0
import org.couch.item.artist 1.0

import "../components"

CouchTabView {
    id: tabView
    tabbarBackgroundColor: highlightColor
    tabbarSelectedColor: highlightColor
    tabbarBackground: Rectangle {
        anchors.fill: parent
        color: highlightColor
        opacity: highlightOpacity
    }
    property MusicFilter searchFilter: MusicFilter {}
    property bool reloadActive: false

    leftCorner: CouchSearchBox {
        focus: true
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        color: styleData.selected ? tabbarSelectedColor : "transparent"
        onAccepted: {
            searchFilter.text = text;
        }
    }
    leftCornerContent: MusicGrid {
        filter: searchFilter
        autoload: false
        onItemClicked: {
            tabView.itemClicked(item);
        }
        Connections {
            target: filter
            onTextChanged: {
                itemList = music.load(searchFilter)
            }
        }
    }

    signal itemClicked(variant item)

    CouchTab {
        title: "home"
        MusicHome {
            onItemClicked: {
                tabView.itemClicked(item);
            }
        }
    }
}
