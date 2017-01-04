import QtQuick 2.4

ContentForm {
    tabBar.onClicked: {
        var musicView = tabView.children[tabView.currentIndex];
        musicView.searchVisible = true;
        musicView.searchField.focus = true;
    }

    function scrollTo(item, offset) {
        if (!offset) {
            offset = 0;
        }

        var c = item.mapToItem(flickable, 0, 0);
        var y = c.y + flickable.contentY - offset;
        flickable.contentY = y > 0 ? y : 0;
    }

    function scrollToMiddle(item) {
        scrollTo(item, lineHeight * 6);
    }

    Behavior on flickable.contentY {
        SmoothedAnimation {
            duration: 300
        }
    }
}
