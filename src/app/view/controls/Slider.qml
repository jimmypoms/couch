import QtQuick 2.4

SliderForm {
    signal valueManuallyChanged()

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                           (handle ? handle.implicitWidth : 0) + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                            (handle ? handle.implicitHeight : 0) + topPadding + bottomPadding)

    Keys.onLeftPressed: {
        decrease();
        valueManuallyChanged();
    }
    Keys.onRightPressed: {
        increase();
        valueManuallyChanged();
    }
}
