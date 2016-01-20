import QtQuick 2.2

Item {
    id: autohide
    property bool inhibit: false
    property bool shouldHide: false
    property int interval: 3000

    Timer {
        id: autohideTimer
        interval: autohide.interval
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