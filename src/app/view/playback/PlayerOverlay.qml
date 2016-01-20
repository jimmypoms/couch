import QtQuick 2.2
import QtQuick.Layouts 1.2

import org.couch.player 1.0

import "../components"

Item {
    id: overlay

    property color highlightColor: "black"
    property real highlightOpacity: 0.5

    Behavior on opacity {
        PropertyAnimation {
            duration: 250
        }
    }

    MouseArea {
        id: headerMouseArea
        hoverEnabled: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: dp(100)
        PlayerHeader {
            id: headerView
            height: dp(80)
            highlightColor: root.highlightColor
            highlightOpacity: root.highlightOpacity
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top

            onBackClicked: {
                if (autohide.shouldHide) {
                    autohide.reset();
                } else {
                    root.backClicked();
                }
            }

            Keys.enabled: !autohide.shouldHide
            Keys.onDownPressed: {
                autohide.reset();
                controlView.forceActiveFocus();
            }
        }
        PlayerBuffering {
            id: bufferingView
            highlightColor: root.highlightColor
            highlightOpacity: root.highlightOpacity
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: headerView.bottom
        }
    }

    MouseArea {
        id: controlsMouseArea
        hoverEnabled: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: dp(90)
        Rectangle {
            id: curtain
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: progressSlider.top
            anchors.bottom: parent.bottom
            color: highlightColor
            opacity: highlightOpacity
        }
        CouchSlider {
            id: progressSlider
            anchors.bottom: controlView.top
            anchors.right: parent.right
            anchors.left: parent.left
            height: dp(30)
            maximumValue: player.duration
            value: player.position
            onValueUpdated: {
                player.position = value;
            }
            Keys.enabled: !autohide.shouldHide
            Keys.onUpPressed: {
                autohide.reset();
                headerView.forceActiveFocus()
            }
            Keys.onDownPressed: {
                autohide.reset();
                controlView.forceActiveFocus();
            }
        }
        FocusScope {
            id: controlView
            focus: true
            height: dp(60)
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom

            Keys.enabled: !autohide.shouldHide
            Keys.onUpPressed: {
                autohide.reset();
                progressSlider.forceActiveFocus()
            }

            RowLayout {
                id: playerActions
                anchors.fill: parent

                CouchIconButton {
                    id: playButton
                    focus: true
                    focusColor: "grey"
                    anchors.verticalCenter: parent.verticalCenter
                    source: "../images/icon-play.svg"
                    Layout.fillHeight: true
                    Layout.preferredWidth: dp(60)

                    Keys.enabled: !autohide.shouldHide
                    Keys.onRightPressed: {
                        autohide.reset();
                        nextButton.forceActiveFocus();
                    }
                    Keys.onUpPressed: {
                        autohide.reset();
                        progressSlider.forceActiveFocus();
                    }
                }
                CouchIconButton {
                    id: nextButton
                    focusColor: "grey"
                    anchors.verticalCenter: parent.verticalCenter
                    source: "../images/icon-next.svg"
                    margins: dp(20)
                    Layout.fillHeight: true
                    Layout.preferredWidth: dp(60)

                    Keys.enabled: !autohide.shouldHide
                    Keys.onLeftPressed: {
                        autohide.reset();
                        playButton.forceActiveFocus();
                    }
                    Keys.onUpPressed: {
                        autohide.reset();
                        progressSlider.forceActiveFocus();
                    }
                }
                Row {
                    Layout.minimumWidth: dp(300)
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Text {
                        text: formatMicroseconds(player.position)
                        color: "grey"

                        font.weight: Font.Light
                        font.pointSize: fp(9)
                    }
                    Text {
                        text: " / "
                        color: "grey"

                        font.weight: Font.Light
                        font.pointSize: fp(9)
                    }
                    Text {
                        text: formatMicroseconds(player.duration)
                        color: "grey"

                        font.weight: Font.Light
                        font.pointSize: fp(9)
                    }
                }
                Item {
                    Layout.fillWidth: true
                }
            }
        }
    }

    CouchAutohide {
        id: autohide
        inhibit: controlsMouseArea.containsMouse || headerMouseArea.containsMouse || player.playbackStatus != CouchPlayer.Playing
        onShouldHideChanged: if (shouldHide) {
            overlay.opacity = 0;
        } else {
            overlay.opacity = 1;
        }
    }

    Keys.onPressed: {
        if (autohide.shouldHide) {
            event.accepted = true;
        }
        autohide.reset();
    }
    onVisibleChanged: if (visible) {
        autohide.reset()
        playButton.forceActiveFocus();
    }
}