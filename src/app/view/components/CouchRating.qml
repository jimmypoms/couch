import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root

    property int count: 5
    property real iconSize: root.width/count
    property int margins: dp(5)
    property color iconColor: "yellow"
    property real value: 0
    property real maxValue: 1

    height: iconSize

    Item {
        id: ratingContainer
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: value/maxValue * parent.width
        clip: true

        Row {
            id: ratingStars
            Repeater {
                model: root.count

                Image {
                    fillMode: Image.PreserveAspectFit
                    sourceSize: Qt.size(iconSize, iconSize)
                    source: "../images/icon-star.svg"
                    visible: true
                }
            }
        }
    }

    ColorOverlay {
        id: curtain
        anchors.fill: parent
        source: ratingStars
        color: "white"
        opacity: 0.5
    }

    ColorOverlay {
        id: overlay
        anchors.fill: ratingContainer
        source: ratingContainer
        color: iconColor
    }
}
