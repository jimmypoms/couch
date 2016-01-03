import QtQuick 2.0

Rectangle {
    color: "transparent"

    property alias highlightColor: curtain.color
    property alias highlightOpacity: curtain.opacity

    Rectangle {
        id: curtain
        anchors.fill: parent
        color: highlightColor
        opacity: highlightOpacity
    }

}
