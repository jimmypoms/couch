import QtQuick 2.2
import QtQuick.Layouts 1.2

import org.couch.sourcelist 1.0

import "../components"

FocusScope {
    id: root

    RowLayout {
        id: container
        spacing: dp(10)
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        Repeater {
            id: repeater
            model: movies.providers
            delegate: CouchSourcesList {
                name: modelData.name
                sourceList: movie.sources(modelData)
                loading: sourceList ? sourceList.loading : false

                Layout.preferredWidth: dp(200)
                Layout.alignment: Qt.AlignBottom | Qt.AlignLeft
                Layout.fillHeight: true
            }
        }
    }
}

