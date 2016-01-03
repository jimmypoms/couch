import QtQuick 2.2

Column {
    id: container
    spacing: 5
    property string text: ""
    property alias title: title.text
    property int pointSize: fp(9)

    Text {
        id: title
        font.weight: Font.Normal
        font.pointSize: pointSize
        width: parent.width

        wrapMode: Text.WordWrap
        elide: Text.ElideRight
        color: "white"
    }

    Text {
        id: text
        text: container.text
        font.weight: Font.Light
        font.pointSize: pointSize
        width: parent.width

        wrapMode: Text.WordWrap
        color: "white"
    }
}
