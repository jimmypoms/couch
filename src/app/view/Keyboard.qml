import QtQuick 2.4

KeyboardForm {
    Behavior on height {
        SmoothedAnimation {
            duration: 300
        }
    }
}
