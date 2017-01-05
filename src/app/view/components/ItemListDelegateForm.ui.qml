import QtQuick 2.4
import QtQuick.Layouts 1.3
import "../controls"

Item {
    id: delegate

    property alias image: image
    property alias errorImage: errorImage
    property alias placeholderImage: placeholderImage
    property alias indicator: busyIndicator
    property bool viewFocused: false
    property real lineHeight: 50
    property url placeholder: "../images/media-placeholder.svg"
    property bool focused: delegate.focus && delegate.viewFocused
    property variant item: ListElement {
    }

    height: lineHeight * 6
    opacity: focused ? 1 : 0.5

    Image {
        id: image
        source: item ? (item.cover ? item.cover : (item.metadata ? item.metadata.image : "")) : ""
        fillMode: Image.PreserveAspectFit
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        anchors.top: parent.top
        height: lineHeight * 4
    }

    Image {
        id: errorImage
        source: placeholder
        fillMode: Image.PreserveAspectFit
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        anchors.top: parent.top
        height: lineHeight * 4
        visible: false
    }

    Image {
        id: placeholderImage
        source: placeholder
        fillMode: Image.PreserveAspectFit
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter
        anchors.top: parent.top
        height: lineHeight * 4
        visible: false
    }

    BusyIndicator {
        id: busyIndicator

        anchors.verticalCenter: image.verticalCenter
        visible: false
    }

    MediumLabel {
        id: title
        height: delegate.lineHeight * 2
        text: item ? item.name : ""
        verticalAlignment: Text.AlignTop
        anchors.top: image.bottom
        anchors.topMargin: 10
        visible: focused ? true : false
        opacity: focused ? 1 : 0
    }

    states: [
        State {
            name: "loading"
            when: image.status == Image.Loading
            PropertyChanges {
                target: busyIndicator
                visible: true
                running: true
                width: 100
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
