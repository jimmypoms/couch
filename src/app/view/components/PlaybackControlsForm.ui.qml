import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

import "../controls"

FocusScope {
    id: component

    property int contentMargin: 8
    property int duration: player.duration
    property int position: player.position
    property bool hasPlaybackControls: player.hasNext || player.hasPrevious

    property variant currentItem: player.currentItem
    property string title: currentItem ? currentItem.name : ""
    property alias positionLabel: positionLabel
    property alias durationLabel: durationLabel
    property alias playButton: playButton
    property alias progressBar: progressBar

    Rectangle {
        anchors.fill: parent

        color: Material.primary
    }

    Item {
        anchors.fill: parent
        anchors.leftMargin: contentMargin
        anchors.rightMargin: contentMargin

        Row {
            id: playbackControls

            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left

            spacing: 8

            Icon {
                id: previousIcon

                source: "../images/icon-previous.svg"
                enabled: player.hasPrevious

                anchors.verticalCenter: parent.verticalCenter
            }

            PlaceholderImage {
                id: playImage

                clip: true
                source: currentItem ? currentItem.metadata.image : ""
                placeholder: "../images/media-placeholder.svg"
                height: parent.height
                width: height

                IconButton {
                    id: playButton

                    anchors.fill: parent

                    padding: 16

                    focus: true
                    source: player.playing ? "../images/icon-pause.svg" : "../images/icon-play.svg"
                }
            }

            Icon {
                id: nextIcon

                source: "../images/icon-next.svg"
                enabled: player.hasNext

                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Row {
            spacing: 8

            anchors.centerIn: parent

            MediumLabel {
                id: positionLabel
            }
            ProgressBar {
                id: progressBar

                from: 0
                to: component.duration
                value: component.position
                implicitWidth: component.width / 5 * 3

                anchors.verticalCenter: parent.verticalCenter
            }
            MediumLabel {
                id: durationLabel
            }
        }
    }
}

