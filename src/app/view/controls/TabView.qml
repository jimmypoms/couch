import QtQuick 2.4

TabViewForm {
    onFocusChanged: {
        stack.children[currentIndex].focus = focus;
    }
}
