import QtQuick 2.4

ItemListViewForm {
    signal itemClicked(var item);
    signal aboutToReachEnd();

    onFocusChanged: {
        if (focus && currentIndex === -1) {
            currentIndex = 0;
        }
    }

    onContentXChanged: {
        if (contentWidth - contentX - width/2 < width) {
            aboutToReachEnd();
        }
    }
}
