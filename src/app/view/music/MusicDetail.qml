import QtQuick 2.4

MusicDetailForm {
    signal itemClicked(var item)

    onItemClicked: {
        play(item);
    }

    playAllButton.onClicked: {
        play(artist);
    }

    actions.onFocusChanged: {
        if (actions.focus) {
            scrollToMiddle(actions);
        }
    }

    albums.onFocusChanged: {
        if (albums.focus) {
            scrollToMiddle(albums);
        }
    }

    albums.onItemClicked: {
        play(item);
    }
}
