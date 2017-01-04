import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Templates 2.0 as T

T.ApplicationWindow {
    id: window

    color: "#ffffff"

    overlay.modal: Rectangle {
        color: "#7f28282a"
    }

    overlay.modeless: Rectangle {
        color: "#1f28282a"
    }
}
