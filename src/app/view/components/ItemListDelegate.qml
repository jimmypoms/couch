import QtQuick 2.4

ItemListDelegateForm {
    width: state === "error"
           ? errorImage.implicitWidth
           : state === "empty"
           ? placeholderImage.implicitWidth
           : Math.max(image.implicitWidth, indicator.width)

    Behavior on width {
        SmoothedAnimation {
            duration: 200
        }
    }
}
