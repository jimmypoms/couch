import QtQuick 2.4

DropdownButtonForm {
    Keys.onPressed: {
        if (!enabled || !popup.visible) {
            return;
        }

        switch (event.key) {
        case Qt.Key_Enter:
        case Qt.Key_Return:
            event.accepted = true;
            listview.currentItem.clicked();
        }
    }
    Keys.onUpPressed: {
        if (popup.visible) {
            if (listview.currentIndex > 0) {
                --listview.currentIndex
            } else {
                event.accepted = false;
            }
        } else if (KeyNavigation && KeyNavigation.up) {
            KeyNavigation.up.focus = true;
        }
    }
    Keys.onDownPressed: {
        if (popup.visible) {
            if (listview.currentIndex < contentModel.length - 1) {
                ++listview.currentIndex;
            } else {
                event.accepted = false;
            }
        } else if (KeyNavigation && KeyNavigation.down) {
            KeyNavigation.down.focus = true;
        }
    }
}
