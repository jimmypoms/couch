import QtQuick 2.4

SearchBarForm {
    Keys.onEscapePressed: {
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
