import QtQuick 2.4

SearchBarForm {
    Keys.onEscapePressed: {
        if (Qt.inputMethod.visible) {
            Qt.inputMethod.hide();
            return;
        }

        text = "";
        if (KeyNavigation.down) {
            KeyNavigation.down.forceActiveFocus();
        }
    }

    Behavior on textField.opacity {
        OpacityAnimator {
            duration: 100
        }
    }
    Behavior on hintLabel.opacity {
        OpacityAnimator {
            duration: 100
        }
    }
}
