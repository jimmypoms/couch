import QtQuick 2.4

ItemListViewForm {
    signal itemClicked(var item);

    onFocusChanged: {
        if (focus && currentIndex === -1) {
            currentIndex = 0;
        }
    }
}
