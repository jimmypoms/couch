import QtQuick 2.0
import QtQuick.Layouts 1.2

FocusScope {
    id: root

    property alias model: repeater.model
    property alias delegate: repeater.delegate
    property alias count: repeater.count

    property real spacing: dp(10)
    property int currentIndex: 0
    property bool focusableChildren: layout.visibleChildren.length > 0

    property bool __focused: false
    onVisibleChanged: if (visible) reinitializeFocus();
    function reinitializeFocus() {
        var item;
        var l = repeater.count;
        for (var i = 0; i < l; ++i) {
            item = repeater.itemAt(i);
            if (item.visible) {
                item.focus = true;
                return;
            }
        }
    }

    RowLayout {
        id: layout

        anchors.fill: parent
        spacing: root.spacing

        Repeater {
            id: repeater
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            visible: false

            onItemAdded: {
                if (!__focused && item.visible) {
                    __focused = true;
                    item.focus = true;
                }
            }
            onItemRemoved: {
                item.focus = false;
            }
            Keys.onPressed: {
                switch (event.key) {
                    case Qt.Key_Left:
                        if (index !== 0) {
                            currentIndex = index -1
                            repeater.itemAt(currentIndex).forceActiveFocus();
                            event.accepted = true;
                        }
                        break;
                    case Qt.Key_Right:
                        if (index !== count) {
                            currentIndex = index + 1;
                            repeater.itemAt(currentIndex).forceActiveFocus();
                            event.accepted = true;
                        }
                        break;
                }
            }
        }
    }
}