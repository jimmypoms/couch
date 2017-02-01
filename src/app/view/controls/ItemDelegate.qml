import QtQuick 2.4

ItemDelegateForm {
    id: control

    Keys.onPressed: {
        if (!enabled) {
            return;
        }

        switch (event.key) {
        case Qt.Key_Enter:
        case Qt.Key_Return:
            event.accepted = true;
            control.clicked();
        }
    }
}
