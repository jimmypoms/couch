import QtQuick 2.4

KeyboardForm {

    enter: Transition {
        NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; easing.type: Easing.OutCubic; duration: 150 }
    }

    exit: Transition {
        NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; easing.type: Easing.OutCubic; duration: 150 }
    }

    Component.onCompleted: {
        contentItem.Keys.upPressed.connect(function(event) {
            if (!visible) {
                event.accepted = false;
            } else if (KeyNavigation && KeyNavigation.up) {
                KeyNavigation.up.forceActiveFocus();
            }
        });
        contentItem.Keys.downPressed.connect(function(event) {
            if (!visible) {
                event.accepted = false;
            } else if (KeyNavigation && KeyNavigation.down) {
                KeyNavigation.down.forceActiveFocus();
            }
        });
        contentItem.clicked.connect(clicked);
        contentItem.backspace.connect(backspace);
    }
}
