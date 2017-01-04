import QtQuick 2.4

HeaderForm {
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
