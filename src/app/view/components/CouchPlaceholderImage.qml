import QtQuick 2.0

Item {
    id: root
    property alias source: intendedImage.source
    property var sourceList: []
    property alias placeholder: placeholderImage.source
    clip: true

    Image {
        id: placeholderImage
        width: parent.width
        verticalAlignment: Image.AlignVCenter

        fillMode: Image.PreserveAspectCrop
    }

    Grid {
        anchors.fill: parent
        opacity: sourceList.length > 1
        columns: 2
        spacing: dp(2)

        Repeater {
            model: Math.min(4, sourceList.length)
            delegate: Image {
                source: sourceList[index]
                fillMode: Image.PreserveAspectFit
                width: (root.width / 2) - dp(1)
                height: (root.height / 2) - dp(1)
            }
        }
    }

    Image {
        id: intendedImage
        width: parent.width
        height: parent.height

        opacity: 0
        fillMode: Image.PreserveAspectCrop
        onStatusChanged: {
            if (status === Image.Ready) {
                intendedImage.opacity = 1;
            }
            if (status === Image.Loading) {
                intendedImage.opacity = 0;
            }
        }

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }
}
