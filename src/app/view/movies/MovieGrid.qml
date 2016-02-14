import QtQuick 2.2

import org.couch.filter.movie 1.0

import "../components"

CouchGridView {
    id: scope
    focus: true

    anchors.fill: parent
    anchors.margins: parent.width * 0.02

    cellWidth: parent.width * 0.16
    cellHeight: cellWidth * 1.2

    property MovieFilter filter: MovieFilter {}
    property var itemList: {'loading': false}
    property bool autoload: true
    loading: itemList.loading
    items: itemList
    Component.onCompleted: {
        if (autoload) {
            itemList = movies.load(scope.filter)
        }
    }

    signal itemClicked(variant item)

    delegate: CouchItemDelegate {
        width: GridView.view.cellWidth
        height: GridView.view.cellHeight

        placeholder: "../images/placeholder-movie.svg"
        containerColor: highlightColor
        item: modelData
        onClicked: {
            itemClicked(item);
        }
    }

}
