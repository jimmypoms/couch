import QtQuick 2.4

MusicDetailForm {
    signal itemClicked(var item)

    onItemClicked: {
        play(item);
    }

    actions.onFocusChanged: {
        if (actions.focus) {
            scrollTo(info);
        }
    }
}
