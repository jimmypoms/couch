import QtQuick 2.4

StackViewForm {
    Keys.onBackPressed: {
        if (depth === 1) {
            event.accepted = false;
        } else {
            pop();
        }
    }
    Keys.onEscapePressed: {
        if (depth === 1) {
            event.accepted = false;
        } else {
            pop();
        }
    }

    onCurrentItemChanged: {
        if (currentItem) {
            currentItem.focus = true;
        }
    }
}
