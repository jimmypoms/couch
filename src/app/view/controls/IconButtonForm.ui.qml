import QtQuick 2.4

Button {
    id: control

    property alias icon: icon.source
    property alias iconHeight: icon.sourceSize.height

    leftPadding: 5
    rightPadding: 5
    topPadding: 5
    bottomPadding: 5

    contentItem: Image {
        id: icon
        sourceSize.height: 18
        fillMode: Image.PreserveAspectCrop
        opacity: control.enabled ? 1 : 0.3
    }
}
