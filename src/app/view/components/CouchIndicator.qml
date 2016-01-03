import QtQuick 2.2

Text {
    property bool running: false

    text: "loading..."
    font.weight: Font.Light
    font.pointSize: fp(9)
    width: parent.width

    wrapMode: Text.WordWrap
    color: "white"
}
