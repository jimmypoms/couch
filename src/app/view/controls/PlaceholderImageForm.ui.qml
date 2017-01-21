import QtQuick 2.4
import QtQuick.Controls.Material 2.0

Item {
    id: control

    property alias source: image.source
    property alias error: errorImage.source
    property alias placeholder: placeholderImage.source

    property alias image: image
    property alias errorImage: errorImage
    property alias placeholderImage: placeholderImage

    Image {
        id: image

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        fillMode: Image.PreserveAspectFit
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
    }

    Image {
        id: errorImage

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        source: placeholderImage.source
        fillMode: Image.PreserveAspectFit
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        visible: false
    }

    Image {
        id: placeholderImage

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        fillMode: Image.PreserveAspectFit
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        visible: false
    }

    BusyIndicator {
        id: busyIndicator

        anchors.centerIn: parent

        width: 80
        height: 80
        visible: false
    }

    states: [
        State {
            name: "loading"
            when: image.status == Image.Loading
            PropertyChanges {
                target: busyIndicator
                visible: true
                running: true
            }
        },
        State {
            name: "empty"
            when: image.status == Image.Null
            PropertyChanges {
                target: placeholderImage
                visible: true
            }
        },
        State {
            name: "error"
            when: image.status == Image.Error
            PropertyChanges {
                target: errorImage
                visible: true
            }
        }
    ]
}
