import QtQuick 2.4

ComboBoxForm {
    Keys.onUpPressed: {
        if (popup.visible) {
            event.accepted = false;
        } else if (KeyNavigation && KeyNavigation.up) {
            KeyNavigation.up.focus = true;
        }
    }
    Keys.onDownPressed: {
        if (popup.visible) {
            event.accepted = false;
        } else if (KeyNavigation && KeyNavigation.down) {
            KeyNavigation.down.focus = true;
        }
    }
}
