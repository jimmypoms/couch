import QtQuick 2.4

SearchBarForm {
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
