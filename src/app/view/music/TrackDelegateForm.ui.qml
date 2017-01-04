import QtQuick 2.4
import QtQuick.Layouts 1.3
import Couch 1.0
import "../controls"

FocusScope {
    id: component

    property variant track: Track {}
    property int leftMargin: 10
    property alias playButton: playButton

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: component.leftMargin

        IconButton {
            id: playButton

            focus: true
            icon: "../images/icon-play.svg"

            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
        }

        MediumLabel {
            text: track.metadata.trackPosition + " - " + track.metadata.track

            Layout.fillWidth: true
        }
    }
}
