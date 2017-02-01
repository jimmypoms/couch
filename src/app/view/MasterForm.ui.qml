import QtQuick 2.4
import QtQuick.Layouts 1.3

FocusScope {
    property alias spacing: columnLayout.spacing
    default property alias contentData: columnLayout.data

    ColumnLayout {
        id: columnLayout

        anchors.fill: parent

        spacing: 24
    }
}
