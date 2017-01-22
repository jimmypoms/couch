import QtQuick 2.4
import Couch 1.0

MainForm {
    function showPlayback() {
        flickable.contentY = -height;
        header.focus = true;
    }

    function hidePlayback() {
        flickable.contentY = header.playing ? -header.height : 0;
        content.focus = true;
    }

    function play(item) {
        showPlayback();
        player.play(item);
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

    Behavior on flickable.contentY {
        SmoothedAnimation {
            duration: 300
        }
    }
}
