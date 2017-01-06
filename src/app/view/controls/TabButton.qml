import QtQuick 2.4

TabButtonForm {
    Behavior on icon.width {
        SmoothedAnimation {
            duration: 200
        }
    }
}
