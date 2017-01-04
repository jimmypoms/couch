import QtQuick 2.4

StackViewForm {
    onCurrentItemChanged: {
        if (currentItem) {
            currentItem.focus = true;
        }
    }
}
