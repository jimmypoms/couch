import QtQuick 2.4
import QtQuick.Layouts 1.3

import "controls"

FocusScope {
    id: component

    property int contentMargin: 0
    property int duration: player.duration
    property int position: player.position
    property bool hasPlaybackControls: player.hasNext || player.hasPrevious

    property string title: player.currentItem ? player.currentItem.name : ""
    property alias positionLabel: positionLabel
    property alias durationLabel: durationLabel
    property alias slider: slider

    property alias playButton: playButton
    property alias previousButton: previousButton
    property alias nextButton: nextButton
    property alias stopButton: stopButton

    FocusScope {
        id: content
        anchors.fill: parent
        focus: true

        RowLayout {
            spacing: 10

            anchors.fill: parent
            anchors.leftMargin: contentMargin
            anchors.rightMargin: contentMargin

            KeyNavigation.up: slider

            IconButton {
                id: playButton
                focus: true
                icon: player.playing ? "images/icon-pause.svg" : "images/icon-play.svg"
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                KeyNavigation.right: hasPlaybackControls ? (player.hasPrevious ? previousButton : nextButton) : stopButton
            }
            RowLayout {
                id: playbackControls

                spacing: 5
                visible: hasPlaybackControls

                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                KeyNavigation.left: playButton
                KeyNavigation.right: stopButton

                IconButton {
                    id: previousButton
                    icon: "images/icon-previous.svg"
                    iconHeight: 15
                    enabled: player.hasPrevious
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    KeyNavigation.right: nextButton.enabled ? nextButton : null
                }
                IconButton {
                    id: nextButton
                    icon: "images/icon-next.svg"
                    iconHeight: 15
                    enabled: player.hasNext
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    KeyNavigation.left: previousButton.enabled ? previousButton : null
                }
            }

            RowLayout {
                spacing: 5
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                MediumLabel {
                    id: positionLabel
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                }
                MediumLabel {
                    text: "/"
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                }
                MediumLabel {
                    id: durationLabel
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                }
            }
            MediumLabel {
                id: currentTitle
                text: component.title
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            }
            IconButton {
                id: stopButton
                icon: "images/icon-stop.svg"
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                KeyNavigation.left: hasPlaybackControls ? (player.hasNext ? nextButton : previousButton) : playButton
            }
        }
    }

    Slider {
        id: slider

        height: focus ? 6 : 3
        from: 0
        to: component.duration
        value: component.position
        padding: 0

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        KeyNavigation.down: content
    }
}

