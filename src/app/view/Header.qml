import QtQuick 2.4

HeaderForm {
    signal showSettings()

    headerMenu.onShowSettings: showSettings()

    onFocusChanged: {
        if (state !== "playback") {
            return;
        }

        if (focus) {
            showPlayback();
        } else {
            hidePlayback();
        }
    }
}
