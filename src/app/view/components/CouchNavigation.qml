import QtQuick 2.2
import QtQuick.Controls 1.2

StackView {
    id: stack

    Keys.onEscapePressed: {
        stack.pop();
    }
    Keys.onBackPressed: {
        root.backClicked()
    }
    onCurrentItemChanged: {
        if (currentItem) {
            currentItem.focus = true;
        }
    }

    delegate: StackViewDelegate {
        pushTransition: StackViewTransition {
            PropertyAnimation {
                target: enterItem
                property: "opacity"
                from: 0
                to: 1
            }
            PropertyAnimation {
                target: exitItem
                property: "opacity"
                from: 1
                to: 0
            }
        }
    }
}
