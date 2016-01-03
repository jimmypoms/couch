import QtQuick 2.2

Row {
    id: windowControls

    CouchIconButton {
        id: minimize
        focus: true
        width: dp(30)
        height: dp(30)
        source: "../images/icon-minus.svg"
        iconFocusColor: "yellow"
        onClicked: {
            applicationWindow.visibility = "Windowed";
        }
        KeyNavigation.right: maximize;
    }
    CouchIconButton {
        id: maximize
        width: dp(30)
        height: dp(30)
        iconFocusColor: "#6FFF00"
        source: "../images/icon-plus.svg"
        onClicked: {
            applicationWindow.visibility = "FullScreen";
        }
        KeyNavigation.left: minimize;
        KeyNavigation.right: close;
    }
    CouchIconButton {
        id: close
        width: dp(30)
        height: dp(30)
        iconFocusColor: "red"
        source: "../images/icon-close.svg"
        onClicked: {
            applicationWindow.close()
        }
        KeyNavigation.left: maximize
    }
    // hack to get padding working
    Item {
        width: dp(5)
        height: dp(5)
    }
}
