import QtQuick 2.4
import Couch 1.0

MainForm {
    Loader {
        id: settingsLoader

        property int lineHeight: content.lineHeight

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

    function showPlayback() {
        contentY = -height + header.height;
        header.focus = true;
    }

    function hidePlayback() {
        contentY = 0;
        content.focus = true;
    }

    function play(item) {
        showPlayback();
        player.play(item);
    }

    header.onShowSettings: {
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
