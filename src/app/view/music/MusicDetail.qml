import QtQuick 2.2
import QtQuick.Layouts 1.2

import org.couch.source 1.0

import "../components"

FocusScope {
    id: container
    focus: true

    signal backClicked()
    signal itemClicked()

    onVisibleChanged: {
        if (visible) {
            sourcesView.forceActiveFocus();
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

            source: movie.metadata.backdrop
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
            text: artist.metadata.names
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
            height: parent.height * 0.4

            ColumnLayout {
                Layout.alignment: Qt.AlignTop
                Layout.preferredWidth: parent.width * 0.25

                Text {
                    Layout.alignment: Qt.AlignRight
                    text: qsTr("directors")

                    color: "white"
                    font.weight: Font.Normal
                    font.pointSize: fp(10)
                }

                Repeater {
                    model: movie.metadata.directors
                    delegate: Text {
                        Layout.alignment: Qt.AlignRight

                        text: modelData
                        color: "white"
                        font.weight: Font.Light
                        font.pointSize: fp(10)
                    }
                }
                Text {
                    Layout.alignment: Qt.AlignRight

                    text: "-"
                    visible: movie.metadata.directors.length === 0
                    color: "white"
                    font.weight: Font.Light
                    font.pointSize: fp(10)
                }

                Item {height: dp(5)}

                Text {
                    Layout.alignment: Qt.AlignRight
                    text: qsTr("cast")

                    color: "white"
                    font.weight: Font.Normal
                    font.pointSize: fp(10)
                }

                Repeater {
                    model: Math.min(8, movie.metadata.actors.length)
                    delegate: Text {
                        Layout.alignment: Qt.AlignRight

                        text: movie.metadata.actors[index]
                        color: "white"
                        font.weight: Font.Light
                        font.pointSize: fp(10)
                    }
                }
                Text {
                    Layout.alignment: Qt.AlignRight

                    text: "-"
                    visible: movie.metadata.actors.length === 0
                    color: "white"
                    font.weight: Font.Light
                    font.pointSize: fp(10)
                }
            }

            ColumnLayout {
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true
                Layout.fillHeight: true

                Text {
                    Layout.fillWidth: true
                    text: movie.metadata.tagline
                    elide: Text.ElideRight

                    color: "white"
                    font.weight: Font.Normal
                    font.pointSize: fp(10)
                }
                Text {
                    Layout.fillWidth: true

                    color: "white"
                    font.weight: Font.Light
                    font.pointSize: fp(10)
                    text: movie.metadata.description
                    wrapMode: Text.WordWrap
                }
            }

            ColumnLayout {
                Layout.alignment: Qt.AlignTop
                Layout.preferredWidth: parent.width * 0.25

                Text {
                    Layout.fillWidth: true
                    text: qsTr("rating")

                    color: "white"
                    font.weight: Font.Normal
                    font.pointSize: fp(10)
                }
                CouchRating {
                    id: rating
                    value: movie.metadata.rating

                    width: dp(150)
                    anchors.margins: dp(10)
                }

                Item {height: dp(5)}

                Text {
                    Layout.fillWidth: true
                    text: qsTr("runtime")

                    color: "white"
                    font.weight: Font.Normal
                    font.pointSize: fp(10)
                }
                Text {
                    Layout.fillWidth: true
                    text: formatMinutes(movie.metadata.runtime)

                    color: "white"
                    font.weight: Font.Light
                    font.pointSize: fp(10)
                }

                Item {height: dp(5)}

                Text {
                    Layout.fillWidth: true
                    text: qsTr("genres")

                    color: "white"
                    font.weight: Font.Normal
                    font.pointSize: fp(10)
                }
                Repeater {
                    model: movie.metadata.genres
                    delegate: Text {
                        Layout.fillWidth: true

                        text: modelData
                        color: "white"
                        font.weight: Font.Light
                        font.pointSize: fp(10)
                    }
                }
                Text {
                    Layout.fillWidth: true

                    text: "-"
                    visible: movie.metadata.genres.length === 0
                    color: "white"
                    font.weight: Font.Light
                    font.pointSize: fp(10)
                }

                Item {height: dp(5)}

                Text {
                    Layout.fillWidth: true
                    text: qsTr("credits")

                    color: "white"
                    font.weight: Font.Normal
                    font.pointSize: fp(10)
                }
                Repeater {
                    model: movie.metadata.credits
                    delegate: Text {
                        Layout.fillWidth: true

                        text: modelData
                        color: "white"
                        font.weight: Font.Light
                        font.pointSize: fp(10)
                    }
                }
                Text {
                    Layout.fillWidth: true

                    text: "-"
                    visible: movie.metadata.credits.length === 0
                    color: "white"
                    font.weight: Font.Light
                    font.pointSize: fp(10)
                }
            }
        }

        FocusScope {
            focus: true
            id: contentActions
            Keys.onUpPressed: {
                closeButton.forceActiveFocus();
            }
            anchors.top: contentDescription.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: dp(50)
            anchors.rightMargin: dp(50)
            height: parent.height * 0.3

            RowLayout {
                anchors.fill: parent

                CouchRow {
                    id: sourcesView
                    focus: true

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    model: movies.providers
                    delegate: CouchSourcesList {
                        name: modelData.name
                        sourceList: movie.sources(modelData)
                        loading: sourceList ? sourceList.loading : false

                        Layout.preferredWidth: dp(200)
                        Layout.alignment: Qt.AlignBottom | Qt.AlignLeft
                        Layout.fillHeight: true
                    }

                    Keys.onPressed: {
                        if (event.key === Qt.Key_Right && actionsView.focusableChildren) {
                            actionsView.forceActiveFocus();
                            event.accepted = true;
                        }
                    }
                }

                CouchRow {
                    id: actionsView

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    property var actionList: movies.actions(movie)
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
        Item {
            id: contentSimilar
            anchors.top: contentActions.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            height: parent.height * 0.3
        }
    }
}
