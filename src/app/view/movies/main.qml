import QtQuick 2.2

import "../components"

CouchNavigation {
    id: navigation
    anchors.fill: parent
    initialItem: movieTabView

    property color highlightColor: "red"
    property real highlightOpacity: 0.5

    MovieTabView {
        id: movieTabView
        focus: true

        onItemClicked: {
            loadDetail(item);
        }
    }

    Loader {
        id: movieDetailLoader
        property variant movie: null
    }

    Connections {
        target: movieDetailLoader.item
        onBackClicked: {
            navigation.pop(movieDetailLoader.item);
        }
        onItemClicked: {
            loadDetail(item);
        }
    }

    Component.onCompleted: {
        if (movies.providers.length === 0) {
            movieTabView.hideItems();
            var component = Qt.createComponent("../components/CouchInfoBox.qml");
            var info = component.createObject(movieTabView, {
                text: qsTr("no providers loaded"),
                'anchors.fill': movieTabView
            });
            if (info === null) {
                console.log("Error creating object: "+component.errorString());
            }
        }
    }

    function loadDetail(item) {
        movies.loadItem(item);
        movieDetailLoader.movie = item;
        movieDetailLoader.source = "MovieDetail.qml";

        navigation.push(movieDetailLoader);
    }
}
