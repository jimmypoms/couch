import QtQuick 2.4

SearchFieldForm {
    id: control

    onStateChanged: {
        if (state === "focused") {
            keyboard.open();
        } else {
            keyboard.close();
        }
    }

    keyboard.onOpened: {
        keyboard.contentItem.forceActiveFocus();
    }

    keyboard.onClicked: {
        var length = textField.text.length;
        textField.insert(length, character);
    }

    keyboard.onBackspace: {
        var length = textField.text.length;
        textField.remove(length - 1, length);
    }
}
