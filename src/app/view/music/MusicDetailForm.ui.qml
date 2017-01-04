import QtQuick 2.4
import QtQuick.Layouts 1.3
import Couch 1.0

import ".."
import "../controls"
import "../components"

Detail {
    id: component

    property variant artist: Artist {}
    property int lineHeight: 40
    property int listHeight: lineHeight * 6
    property alias info: info
    property alias actions: actions
    property alias albumList: albums

    title: artist.metadata ? artist.metadata.name : artist.name

    RowLayout {
        id: info

        height: lineHeight * 6
    }

    FocusScope {
        id: actions

        focus: true
        height: lineHeight * 2
        Layout.fillWidth: true

        KeyNavigation.down: albums

        RowLayout {
            Button {
                text: qsTr("play all")
                focus: true

                Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            }

            ListView {
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

                delegate: Button {
                    text: modelData.text
                    visible: modelData.enabled

                    highlightColor: "chocolate"
                }
            }
        }
    }

    MediumLabel {
        text: qsTr("Albums")
    }

    ItemListView {
        id: albums

        Layout.fillWidth: true
        model: artist.albums
        lineHeight: component.lineHeight

        KeyNavigation.up: actions

        delegate: AlbumDelegate {
            list: ListView.view
            viewFocused: albums.currentIndex === index
            lineHeight: albums.lineHeight
            trackList.width: albums.width
            album: modelData

            Keys.onEnterPressed: {
                itemClicked(modelData);
            }
            Keys.onReturnPressed: {
                itemClicked(modelData);
            }
        }
    }
}
