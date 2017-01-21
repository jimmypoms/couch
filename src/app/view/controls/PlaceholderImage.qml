import QtQuick 2.4

PlaceholderImageForm {
    id: control

    implicitWidth: state === "error"
           ? errorImage.implicitWidth
           : state === "empty"
           ? placeholderImage.implicitWidth
           : Math.max(image.implicitWidth, control.height)

    Behavior on implicitWidth {
        SmoothedAnimation {
            duration: 200
        }
    }
}
