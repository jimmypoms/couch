import QtQuick 2.2

import org.couch.filter.music 1.0

import "../components"

CouchGridView {
    id: scope
    focus: true

    anchors.fill: parent
    anchors.margins: parent.width * 0.02

    cellWidth: parent.width * 0.16
    cellHeight: cellWidth * 1.2

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

    delegate: MusicDelegateBig {
        width: GridView.view.cellWidth
        height: GridView.view.cellHeight
        z: activeFocus ? 2 : 1
        onClicked: {
            itemClicked(modelData);
        }
        Keys.onEnterPressed: {
            itemClicked(modelData);
        }
        Keys.onReturnPressed: {
            itemClicked(modelData);
        }
    }

}
