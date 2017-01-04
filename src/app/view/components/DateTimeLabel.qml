import QtQuick 2.4
import QtQml 2.2

DateTimeLabelForm {
    id: dateTimeLabel

    Component.onCompleted: {
        timer.start();
    }

    function update() {
        var date = new Date();
        dateTimeLabel.text = date.toLocaleString(Qt.locale("en_GB"), "dddd MMMM d, hh:mm");
    }

    Timer {
        id: timer
        interval: 1
        repeat: true
        triggeredOnStart: true
        onTriggered: dateTimeLabel.update()
    }
}
