import QtQuick 2.4

TabBarForm {
    id: control

    Binding {
        target: background
        property: "color"
        value: "transparent"
    }

    onFocusChanged: {
        contentItem.focus = focus;
    }

    onTabViewChanged: {
        tabView.Keys.onUpPressed.connect(function() {
            control.focus = true;
        });
        control.Keys.onDownPressed.disconnect(focusTabView);
        control.Keys.onDownPressed.connect(focusTabView)
        control.currentIndexChanged.disconnect(pushCurrentIndex);
        control.currentIndexChanged.connect(pushCurrentIndex)
    }

    function focusTabView() {
        tabView.focus = true;
    }

    function pushCurrentIndex() {
        tabView.currentIndex = control.currentIndex;
    }
}
