import QtQuick 2.4
import QtQuick.Layouts 1.3
import Couch 1.0
import "controls"

FocusScope {
    id: control

    property string title: ""
    property alias flickable: flickable
    property alias spacing: columnLayout.spacing
    default property alias contentChildren: columnLayout.children

    LargeLabel {
        id: titleLabel
        text: control.title

        anchors.top: parent.top
        anchors.left: parent.left
    }

    Flickable {
        id: flickable

        clip: true

        anchors.top: titleLabel.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        ColumnLayout {
            id: columnLayout

            spacing: 20
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
        }
    }
}
