import QtQuick 2.4

AlbumDelegateForm {
    albumDelegate.onActiveFocusChanged: {
        if (albumDelegate.activeFocus) {
            scrollToMiddle(albumDelegate);
        }
    }

    trackList.onFocusChanged: {
        list.keyNavigationEnabled = !trackList.focus;
        if (trackList.focus) {
            scrollTo(trackList, lineHeight * 3 - 5);
        }
    }
}
