import QtQuick 2.4
import QtQuick.Layouts 1.3

FocusScope {
    default property alias contentChildren: stack.children
    property alias currentIndex: stack.currentIndex
    property alias stack: stack

    x: stack.x
    y: stack.y
    width: stack.implicitWidth
    height: stack.implicitHeight

    StackLayout {
        id: stack
        focus: true
        anchors.fill: parent
    }
}

