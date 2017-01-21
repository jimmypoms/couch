import QtQuick 2.4
import QtQuick.Layouts 1.3

FocusScope {
    default property alias contentData: stack.data
    property alias currentIndex: stack.currentIndex
    property StackLayout stack: StackLayout {
        id: stack
        anchors.fill: parent
    }

    x: stack.x
    y: stack.y
    implicitWidth: stack.implicitWidth
    implicitHeight: stack.implicitHeight

    children: [
        stack
    ]
}

