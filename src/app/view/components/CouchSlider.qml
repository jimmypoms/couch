import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Slider {
    id: slider
    property color grooveColor: "#193441"
    property color activeHandleColor: "grey"
    property bool grooveHovered: false

    signal valueUpdated(real value)

    opacity: activeFocus ? 1 : 0.8
    Behavior on opacity {
        NumberAnimation {
            duration: 250
        }
    }
    onPressedChanged: {
        if (pressed) {
            valueUpdated(value);
        }
    }
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            slider.forceActiveFocus();
            slider.grooveHovered = true;
        }
        onExited: {
            slider.grooveHovered = false
        }
    }
    Keys.onLeftPressed: valueUpdated(value)
    Keys.onRightPressed: valueUpdated(value)

    style: SliderStyle {
        handle: Rectangle {
            anchors.bottom: parent.bottom
            width: dp(20)
            height: control.activeFocus ? dp(20) : dp(5)
            color: control.activeFocus ? activeHandleColor : "transparent"

            Behavior on height {
                NumberAnimation {
                    duration: 250
                }
            }
            Behavior on color {
                ColorAnimation {
                    duration: 250
                }
            }
        }

        groove: Rectangle {
            height: control.activeFocus ? dp(10) : dp(5)
            implicitWidth: 100
            color: "transparent"
            border.color: control.activeFocus ? "#333" : "transparent"
            border.width: 1

            Item {
                clip: true
                width: styleData.handlePosition
                height: parent.height
                Rectangle {
                    anchors.fill: parent
                    color: grooveColor
                }
            }

            Behavior on height {
                NumberAnimation {
                    duration: 250
                }
            }
        }
    }
}
