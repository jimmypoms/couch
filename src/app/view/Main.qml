import QtQuick 2.4
import Couch 1.0

MainForm {
    id: main

    Loader {
        id: settingsLoader

        active: false
        source: "settings/Settings.qml"
        visible: false
        opacity: 0
        onFocusChanged: {
            if (focus && item) {
                item.focus = true;
            }
        }
    }

    signal showSettings();

    function showPlayback() {
        main.contentY = -height;
        header.focus = true;
    }

    function hidePlayback() {
        main.contentY = header.playing ? -header.height : 0;
        content.focus = true;
    }

    function play(item) {
        showPlayback();
        player.play(item);
    }

    onShowSettings: {
        settingsLoader.active = true;
        settingsLoader.visible = true;
        settingsLoader.opacity = 1;
        content.push(settingsLoader);
        content.focus = true;
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
