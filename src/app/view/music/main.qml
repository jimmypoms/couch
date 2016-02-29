import QtQuick 2.2

import "../components"

CouchNavigation {
    id: navigation
    anchors.fill: parent
    initialItem: tabView

    property color highlightColor: "green"
    property real highlightOpacity: 0.5

    MusicTabView {
        id: tabView
        focus: true

        onItemClicked: {
            loadDetail(item);
        }
    }

    Loader {
        id: detailLoader
        property variant artist: null
    }

    Connections {
        target: detailLoader.item
        onBackClicked: {
            navigation.pop(detailLoader.item);
        }
        onItemClicked: {
            loadDetail(item);
        }
    }

    Component.onCompleted: {
        if (music.providers.length === 0) {
            tabView.hideItems();
            var component = Qt.createComponent("../components/CouchInfoBox.qml");
            var info = component.createObject(tabView, {
                text: qsTr("no providers loaded"),
                'anchors.fill': tabView
            });
            if (info === null) {
                console.log("Error creating object: "+component.errorString());
            }
        }
    }

    function loadDetail(item) {
        music.loadItem(item);
        detailLoader.artist = item;
        detailLoader.source = "MusicDetail.qml";

        navigation.push(detailLoader);
    }
}
