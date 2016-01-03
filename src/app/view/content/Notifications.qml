import QtQuick 2.0

Column {
    id: notifications

    Item {
        id: warning
        visible: false
        width: parent.width
        height: dp(60)
        property alias text: warningText.text
        Rectangle {
            id: warningBox
            anchors.margins: dp(5)
            anchors.fill: parent
            color: "yellow"
            opacity: 0.8
        }
        Text {
            id: warningText
            anchors.centerIn: warningBox
            anchors.left: parent.left
            anchors.right: parent.right
            color: "white"
            wrapMode: Text.WordWrap
            font.weight: Font.Light
            font.pointSize: fp(10)
        }
    }

    Item {
        id: error
        visible: false
        width: parent.width
        height: dp(60)
        property alias text: errorText.text
        Rectangle {
            id: errorBox
            anchors.margins: dp(5)
            anchors.fill: parent
            color: "red"
            opacity: 0.8
        }
        Text {
            id: errorText
            anchors.centerIn: errorBox
            anchors.left: parent.left
            anchors.right: parent.right
            color: "white"
            wrapMode: Text.WordWrap
            font.weight: Font.Light
            font.pointSize: fp(10)
        }
    }

    function warning(message) {
        warning.text = message;
        warning.visible = true;
    }

    function error(message) {
        error.text = message;
        error.visible = true;
    }

    function clearErrors() {
        error.visible = false;
    }

    function clearWarnings() {
        warning.visible = false;
    }

    function clear() {
        clearErrors();
        clearWarnings();
    }
}
