import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0
import QtGraphicalEffects 1.0

import Couch 1.0
import "controls"

FocusScope {
    id: control

    property string title: ""
    property alias image: headerImage.source
    property alias content: columnLayout
    property int contentMargin: 32
    property alias flickable: flickable
    property alias spacing: columnLayout.spacing
    default property alias contentData: columnLayout.data

    Flickable {
        id: flickable

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: contentMargin

        Item {
            id: header

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            height: 176

            Image {
                id: headerImage

                anchors.fill: parent

                fillMode: Image.PreserveAspectCrop
                visible: false
            }

            Rectangle {
                anchors.fill: headerImage

                color: Material.primary
                visible: headerImage.status === Image.Null
            }

            ColorOverlay {
                anchors.fill: headerImage

                source: headerImage
                color: Qt.rgba(Material.primary.r, Material.primary.g, Material.primary.b, 0.9)
            }

            LargeLabel {
                id: titleLabel
                text: control.title

                anchors.left: parent.left
                anchors.bottom: parent.bottom
                anchors.leftMargin: contentMargin
                anchors.bottomMargin: contentMargin
            }
        }

        ColumnLayout {
            id: columnLayout

            spacing: 24
            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: contentMargin
            anchors.leftMargin: contentMargin
            anchors.rightMargin: contentMargin
        }
    }
}
