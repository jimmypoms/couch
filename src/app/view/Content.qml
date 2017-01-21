import QtQuick 2.4

ContentForm {
    property int centerY: tabView.y

    function scrollTo(item, offset) {
        if (!offset) {
            offset = 0;
        }

        var c = item.mapToItem(flickable, 0, 0);
        var y = c.y + flickable.contentY - offset;
        flickable.contentY = y > 0 ? y : 0;
    }

    function scrollToMiddle(item) {
        scrollTo(item, centerY);
    }

    Behavior on flickable.contentY {
        SmoothedAnimation {
            duration: 300
        }
    }
    Behavior on overlay.opacity {
        OpacityAnimator {
            duration: 100
        }
    }
}
