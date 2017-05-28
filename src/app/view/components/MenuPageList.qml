import QtQuick 2.4

MenuPageListForm {
    Component.onCompleted: {
        list.currentIndex = 0
        list.focus = visible
    }
    onVisibleChanged: list.focus = visible
}
