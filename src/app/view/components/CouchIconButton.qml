import QtQuick 2.2
import QtGraphicalEffects 1.0

import "../animations"

CouchButton {
    id: button
    focusColor: "transparent"

    property alias source: icon.source
    property color iconColor: "white"
    property color iconFocusColor: "white"
    property int margins: dp(5)
    property real size: dp(50)

    width: size
    height: size
    implicitWidth: size
    implicitHeight: size

    Image {
        id: icon
        anchors.centerIn: parent
        sourceSize: Qt.size(parent.width-margins, parent.height-margins)
        visible: false
    }

    ColorOverlay {
        id: overlay
        anchors.fill: icon
        source: icon
        color: iconColor
        opacity: 0.8
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            button.forceActiveFocus();
        }
        onClicked: {
            button.clicked();
        }
    }

    states: State {
        name: "focus"; when: button.activeFocus
        PropertyChanges { target: overlay; color: iconFocusColor; opacity: 1 }
        StateChangeScript { script: bounce.start() }
    }

    BounceAnimation {
        id: bounce
        target: button
    }
}
