import QtQuick 2.0

Item {
    id: root
    property string source: ''
    property var sourceList: []
    property alias placeholder: placeholderImage.source
    property int verticalAlignment: Image.AlignVCenter
    property int horizontalAlignment: Image.AlignHCenter
    clip: true

    Image {
        id: placeholderImage
        width: parent.width
        verticalAlignment: root.verticalAlignment
        horizontalAlignment: root.horizontalAlignment

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
                width: (root.width / 2) - dp(1)
                height: (root.height / 2) - dp(1)
            }
        }
    }

    Image {
        id: intendedImage
        width: parent.width
        height: parent.height
        verticalAlignment: root.verticalAlignment
        horizontalAlignment: root.horizontalAlignment

        source: root.source ? root.source : (sourceList.length === 1 ? sourceList[0] : '')
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
