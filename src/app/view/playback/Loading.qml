import QtQuick 2.0

import "../components"

FocusScope {
    Rectangle {
        color: backgroundColor
        anchors.fill: parent

        onEnabledChanged: if (enabled) {
            cancelButton.forceActiveFocus();
        }

        Image {
            id: image
            anchors.fill: parent
            opacity: 0

            source: player.currentItem ? player.currentItem.metadata.backdrop : ''
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

        Item {
            width: parent.width * 0.5
            height: parent.height * 0.5
            anchors.centerIn: parent

            Text {
                id: title
                text: player.currentSource ? player.currentSource.name : ''
                color: "white"
                font.weight: Font.Normal
                font.pointSize: fp(24)

                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: dp(10)

                wrapMode: Text.WordWrap
                elide: Text.ElideRight
            }

            Text {
                id: loadingText
                anchors.top: title.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: dp(10)

                text: qsTr("loading...")

                color: "white"
                font.weight: Font.Normal
                font.pointSize: fp(11)
            }

            CouchButton {
                id: cancelButton
                text: qsTr("cancel")
                color: "orange"

                anchors.top: loadingText.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.margins: dp(10)

                height: dp(50)
                width: dp(200)

                onClicked: player.stop()
            }
        }
    }
}
