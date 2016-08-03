import QtQuick 2.2
import QtQuick.Layouts 1.2

import org.couch.source 1.0

import "../components"

FocusScope {
    id: container
    focus: true

    property real listMargin: dp(50)
    property real albumDelegateWidth: parent.width * 0.23
    property real albumDelegateSpacing: parent.width * 0.01

    signal backClicked()
    signal itemClicked()

    onVisibleChanged: {
        if (visible) {
            contentActions.forceActiveFocus();
        }
    }

    Rectangle {
        id: backdrop
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        color: backgroundColor

        Image {
            id: image
            anchors.fill: parent
            anchors.topMargin: -dp(80)
            clip: true
            opacity: 0

            source: artist.metadata.backdrop
            fillMode: Image.PreserveAspectCrop
            asynchronous: true

            Behavior on opacity {
                NumberAnimation {
                    duration: 200
                }
            }
            onStatusChanged: {
                if (status === Image.Ready) {
                    image.opacity = 0.2;
                }
                if (status === Image.Loading) {
                    image.opacity = 0;
                }
            }
        }
    }

    Item {
        id: header

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: dp(40)

        Rectangle {
            color: highlightColor
            opacity: highlightOpacity
            anchors.fill: parent
        }
    }

    Row {
        anchors.fill: header
        spacing: dp(5)

        CouchIconButton {
            id: closeButton
            focusColor: "grey"
            size: dp(40)
            anchors.verticalCenter: parent.verticalCenter

            source: "../images/icon-back.svg"
            onClicked: {
                container.backClicked();
            }
            Keys.onDownPressed: {
                contentActions.forceActiveFocus();
            }
        }

        Text {
            id: title
            anchors.verticalCenter: parent.verticalCenter
            text: artist.metadata.name
            color: "white"
            font.weight: Font.Normal
            font.pointSize: fp(12)
        }
    }

    Item {
        id: content
        anchors.fill: backdrop
        anchors.topMargin: dp(30)

        RowLayout {
            id: contentDescription
            spacing: dp(30)

            anchors.right: parent.right
            anchors.left: parent.left
            height: parent.height * 0.2
        }

        FocusScope {
            focus: true
            id: contentActions
            Keys.onUpPressed: {
                closeButton.forceActiveFocus();
            }
            Keys.onDownPressed: {
                contentAlbums.forceActiveFocus();
            }
            anchors.top: contentDescription.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: listMargin
            anchors.rightMargin: listMargin
            height: parent.height * 0.2

            RowLayout {
                anchors.fill: parent

                CouchButton {
                    text: "play all"
                    focus: true

                    Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                    Layout.preferredHeight: dp(50)
                    Layout.preferredWidth: dp(200)

                    color: "orange"
                    onClicked: {
                    }
                }

                CouchRow {
                    id: actionsView

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    property var actionList: music.actions(artist)
                    model: actionList
                    delegate: CouchButton {
                        text: modelData.text
                        visible: modelData.enabled

                        Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                        Layout.preferredHeight: dp(50)
                        Layout.preferredWidth: dp(200)

                        color: "chocolate"
                        onClicked: {
                            modelData.trigger();
                        }
                    }

                    Keys.onLeftPressed: {
                        sourcesView.forceActiveFocus()
                    }
                }
            }
        }

        FocusScope {
            id: contentAlbums
            anchors.top: contentActions.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.topMargin: listMargin
            anchors.bottomMargin: listMargin

            Keys.onUpPressed: {
                contentActions.forceActiveFocus();
            }

            CouchListView {
                anchors.fill: parent
                leftMargin: listMargin
                rightMargin: listMargin
                spacing: albumDelegateSpacing

                items: artist.albums
                loading: items.loading
                delegate: AlbumDelegate {
                    item: modelData
                    width: albumDelegateWidth
                    height: parent.height

                    containerColor: highlightColor
                }
            }
        }
    }
}
