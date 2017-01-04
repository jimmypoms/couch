import QtQuick 2.4
import QtQuick.Templates 2.0 as T
import "../controls"

FocusScope {
    id: control

    property alias textField: textField
    property alias keyboard: keyboard

    property alias keyboardHeight: keyboard.height
    property alias keyboardWidth: keyboard.width
    property alias keyboardVisible: keyboard.visible

    property int padding: 10
    property int leftPadding: padding
    property int rightPadding: padding
    property int topPadding: padding
    property int bottomPadding: padding

    property color color: "white"
    property color highlightColor: "green"
    property bool active: state === "focused" || textField.text.length > 0
    property string text: textField.text

    x: textField.x
    y: textField.y
    implicitWidth: textField.width
    implicitHeight: textField.implicitHeight + topPadding + bottomPadding

    Image {
        id: icon

        x: control.leftPadding
        y: control.topPadding + 2
        source: "../images/search-indicator.svg"
        height: textField.contentHeight - 4
        fillMode: Image.PreserveAspectFit
    }

    T.TextField {
        id: textField

        width: contentWidth + leftPadding + rightPadding
        anchors.top: control.top
        anchors.bottom: control.bottom

        leftPadding: control.leftPadding + icon.width + 5
        rightPadding: control.rightPadding
        topPadding: control.topPadding
        bottomPadding: control.bottomPadding
        color: control.color
        font.pointSize: 12

        focus: true
        KeyNavigation.down: keyboardVisible ? keyboard.contentItem : null
    }

    Rectangle {
        id: underline

        anchors.bottom: control.bottom
        anchors.left: control.left

        color: control.color
        width: control.implicitWidth
        height: 2
    }

    Keyboard {
        id: keyboard

        y: control.height
        KeyNavigation.up: control
        KeyNavigation.down: control.KeyNavigation.down

        closePolicy: T.Popup.CloseOnEscape | T.Popup.CloseOnPressOutsideParent
    }

    states: [
        State {
            name: "focused"
            when: control.focus || keyboard.contentItem.activeFocus
            PropertyChanges {
                target: underline
                height: 5
                color: control.highlightColor
            }
        }
    ]
}
