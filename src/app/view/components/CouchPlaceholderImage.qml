import QtQuick 2.0

Item {
    property alias source: intendedImage.source
    property alias placeholder: placeholderImage.source
        clip: true

    Image {
        id: intendedImage
        width: parent.width
        height: parent.height

        opacity: 0
        fillMode: Image.PreserveAspectCrop
        verticalAlignment: Image.AlignVCenter
        onStatusChanged: {
            if (status === Image.Ready) {
                intendedImage.opacity = 1;
                placeholderImage.opacity = 0;
            }
            if (status === Image.Loading) {
                intendedImage.opacity = 0;
                placeholderImage.opacity = 1;
            }
        }

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }
    Image {
        id: placeholderImage
        width: parent.width

        opacity: 1
        fillMode: Image.PreserveAspectCrop
        verticalAlignment: Image.AlignVCenter

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }
}
