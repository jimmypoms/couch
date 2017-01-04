import QtQuick 2.4
import Couch 1.0

MainForm {
    function showPlayback() {
        contentY = -height + header.height;
        header.focus = true;
    }

    function hidePlayback() {
        contentY = 0;
        content.focus = true;
    }

    function play(item) {
        player.play(item);
        showPlayback();
    }

    Component.onCompleted: {
        player.playbackStatusChanged.connect(function() {
            if (player.playbackStatus !== Player.Stopped) {
                showPlayback();
            } else {
                hidePlayback();
            }
        });
    }

    Behavior on contentY {
        SmoothedAnimation {
            duration: 300
        }
    }
}
