import QtQuick 2.2

Text {
    property bool running: visible

    text: "loading..."
    font.weight: Font.Light
    font.pointSize: fp(9)

    wrapMode: Text.WordWrap
    color: "white"
}
