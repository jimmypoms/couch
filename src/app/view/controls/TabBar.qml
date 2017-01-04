import QtQuick 2.4

TabBarForm {
    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)

    onFocusChanged: {
        contentItem.focus = focus;
    }

    Keys.onEnterPressed: clicked();
    Keys.onReturnPressed: clicked();
}
