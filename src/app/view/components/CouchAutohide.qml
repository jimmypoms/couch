import QtQuick 2.2

Item {
    id: autohide
    property bool inhibit: false
    property bool shouldHide: false

    Timer {
        id: autohideTimer
        interval: 2000
        repeat: false
        running: true

        onTriggered: {
            autohide.shouldHide = true;
            autohideTimer.stop();
        }
    }

    onInhibitChanged: if (inhibit) {
        autohide.shouldHide = false;
        autohideTimer.stop();
    } else {
        autohideTimer.start();
    }

    function reset() {
        if (!inhibit) {
            autohide.shouldHide = false;
            autohideTimer.restart();
        }
    }
}