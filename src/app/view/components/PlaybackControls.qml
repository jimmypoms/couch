import QtQuick 2.4

PlaybackControlsForm {
    Keys.onEscapePressed: {
        hidePlayback();
    }
    Keys.onDownPressed: {
        hidePlayback();
    }

    playButton.onClicked: {
        player.togglePlay();
    }

    Keys.onReturnPressed: {
        player.togglePlay();
    }

    Keys.onRightPressed: {
        player.next();
    }

    Keys.onLeftPressed: {
        player.previous();
    }

    onDurationChanged: {
        durationLabel.text = formatMilliseconds(duration);
    }

    onPositionChanged: {
        positionLabel.text = formatMilliseconds(position);
    }

    Component.onCompleted: {
        durationLabel.text = formatMilliseconds(0);
        positionLabel.text = formatMilliseconds(0);
    }

    function formatMilliseconds(milliseconds) {
        var seconds = Math.floor(milliseconds / 1000);
        var hours   = Math.floor(seconds / 3600);
        var minutes = Math.floor((seconds - (hours * 3600)) / 60);
        seconds = seconds - (hours * 3600) - (minutes * 60);

        if (hours && hours < 10) {hours = '0'+hours;}
        if (hours && minutes < 10) {minutes = '0'+minutes;}
        if (seconds < 10) {seconds = '0'+seconds;}
        if (hours && hours !== '00') {
            return hours+':'+minutes+':'+seconds;
        }
        return minutes+':'+seconds;
    }
}
