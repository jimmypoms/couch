import QtQuick 2.2

import org.couch.filter.music 1.0

import "../components"

CouchGridView {
    id: scope
    focus: true

    anchors.fill: parent
    anchors.margins: parent.width * 0.02

    cellWidth: parent.width * 0.16
    cellHeight: cellWidth

    property MusicFilter filter: MusicFilter {}
    property var itemList: {'loading': false}
    property bool autoload: true
    loading: itemList.loading
    items: itemList
    Component.onCompleted: {
        if (autoload) {
            itemList = music.load(scope.filter)
        }
    }

    signal itemClicked(variant item)

    delegate: CouchItemDelegate {
        width: GridView.view.cellWidth
        height: GridView.view.cellHeight

        placeholder: "../images/placeholder-music.svg"
        containerColor: highlightColor
        item: modelData
        imageList: modelData.albumCovers
        onClicked: {
            itemClicked(modelData);
        }
    }

}
