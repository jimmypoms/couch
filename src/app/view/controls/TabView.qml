import QtQuick 2.4

TabViewForm {
    onFocusChanged: {
        children[currentIndex].focus = focus;
    }
}
