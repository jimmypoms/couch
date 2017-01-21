import QtQuick 2.4
import QtQuick.Controls.Material 2.0

import "../controls"

Pane {
    id: component

    property alias image: image
    property bool viewFocused: false
    property alias placeholder: image.placeholder
    property bool focused: component.activeFocus && component.viewFocused
    property string name: item ? item.name : ""
    property variant item

    padding: 0
    implicitHeight: image.height + content.height
    implicitWidth: image.implicitWidth
    z: component.focused ? 3 : 1
    y: component.focused ? -5 : 0
    scale: component.focused ? 1.1 : 1
    transformOrigin: Item.Top

    Material.elevation: component.focused ? 8 : 2

    PlaceholderImage {
        id: image

        anchors.top: parent.top
        anchors.left: parent.left

        source: item.cover ? item.cover : (item.metadata ? item.metadata.image : "")
        placeholder: "../images/media-placeholder.svg"
        height: 216
        opacity: component.focused ? 1 : 0.5
    }

    Rectangle {
        id: content

        anchors.top: image.bottom

        height: 72
        width: component.width
        opacity: component.focused ? 1 : 0.5

        color: Material.primary

        MediumLabel {
            id: title

            text: component.name
            anchors.fill: parent
            padding: 16
            verticalAlignment: Text.AlignTop
            elide: Text.ElideRight
        }
    }
}
