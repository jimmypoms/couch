import QtQuick 2.2

SequentialAnimation {
    id: bounceAnimation
    property alias target: scaleUp.target

    PropertyAnimation {
        id: scaleUp
        properties: "scale"
        from: 1.0
        to: 1.3
        duration: 50
        easing.type: Easing.InOutElastic
    }
    PropertyAnimation {
        id: scaleDown
        target: scaleUp.target
        properties: "scale"
        from: 1.3
        to: 1.0
        duration: 50
        easing.type: Easing.InOutElastic
    }
}
