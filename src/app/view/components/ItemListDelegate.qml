import QtQuick 2.4

ItemListDelegateForm {
    id: component

    signal clicked()

    Keys.onEnterPressed: {
        clicked();
    }

    Keys.onReturnPressed: {
        clicked();
    }

    Behavior on y {
        YAnimator {
            duration: 100
            easing.type: Easing.InOutCubic
        }
    }
    Behavior on scale {
        ScaleAnimator {
            duration: 100
            easing.type: Easing.InOutCubic
        }
    }
}
