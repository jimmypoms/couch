import QtQuick 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0

FocusScope {
    id: container
    implicitWidth: icon.implicitWidth + textInput.implicitWidth + dp(20)
    width: implicitWidth
    implicitHeight: iconSize + 2 * iconMargins
    height: implicitHeight
    property color color: "transparent"
    property color focusColor: "grey"
    property color iconColor: "white"
    property int iconSize: dp(30)
    property int iconMargins: dp(5)

    signal accepted(string text);

    Rectangle {
        id: focusHighlight
        anchors.fill: parent
        color: textInput.activeFocus ? focusColor : container.color
    }

    MouseArea {
        anchors.fill: focusHighlight
        hoverEnabled: true
        onEntered: {
            parent.forceActiveFocus();
        }
    }

    Image {
        id: icon
        source: "../images/icon-search.svg"
        sourceSize: Qt.size(iconSize, iconSize)
        fillMode: Image.PreserveAspectFit
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: iconMargins
        visible: false
        smooth: true
    }

    ColorOverlay {
        id: overlay
        anchors.fill: icon
        source: icon
        color: iconColor
        opacity: 0.8
    }

    TextInput {
        id: textInput
        anchors.left: icon.right
        anchors.right: parent.right
        anchors.leftMargin: iconMargins
        anchors.verticalCenter: parent.verticalCenter

        focus: parent.activeFocus
        color: "white"
        font.weight: Font.Normal
        font.pointSize: fp(9)

        onAccepted: {
            container.accepted(text);
        }
    }

    Rectangle {
        id: border
        anchors.bottom: icon.bottom
        anchors.left: textInput.left
        width: textInput.contentWidth
        height: dp(2)
        color: iconColor
        opacity: overlay.opacity

        Behavior on width {
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }
    }
}
