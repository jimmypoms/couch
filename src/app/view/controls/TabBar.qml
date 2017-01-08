import QtQuick 2.4

TabBarForm {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)

    onFocusChanged: {
        contentItem.focus = focus;
    }

    onTabViewChanged: {
        tabView.Keys.onUpPressed.connect(function() {
            control.focus = true;
        });
        control.currentIndexChanged.connect(function() {
            tabView.currentIndex = control.currentIndex;
        })
    }

    Keys.onEnterPressed: clicked();
    Keys.onReturnPressed: clicked();
}
