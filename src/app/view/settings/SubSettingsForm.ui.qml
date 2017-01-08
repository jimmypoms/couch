import QtQuick 2.4
import QtQuick.Layouts 1.3

FocusScope {
    default property alias contentChildren: columnLayout.children

    x: columnLayout.x
    y: columnLayout.y
    implicitWidth: columnLayout.width
    implicitHeight: columnLayout.implicitHeight

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
    }
}
