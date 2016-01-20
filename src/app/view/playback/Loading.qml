import QtQuick 2.0

Rectangle {
    color: "black"

    Item {
        width: parent.width * 0.5
        height: parent.height * 0.5
        anchors.centerIn: parent

        Image {
            id: detailImage
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.margins: dp(5)
            smooth: false
            fillMode: Image.PreserveAspectFit
            horizontalAlignment: Image.AlignLeft
            source: couch.currentItem ? couch.currentItem.metadata.image : ""
        }

        Text {
            id: title
            text: couch.currentItem ? couch.currentItem.metadata.title : ""
            color: "white"
            font.weight: Font.Normal
            font.pointSize: fp(24)

            anchors.left: detailImage.right
            anchors.right: parent.right
            anchors.bottom: loadingText.top
            anchors.margins: dp(10)

            wrapMode: Text.WordWrap
            elide: Text.ElideRight
        }

        Text {
            id: loadingText
            anchors.left: detailImage.right
            anchors.bottom: parent.bottom
            anchors.margins: dp(10)

            text: qsTr("loading...")

            color: "white"
            font.weight: Font.Normal
            font.pointSize: fp(11)
        }
    }
}
