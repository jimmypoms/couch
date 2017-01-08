import QtQuick 2.4

GeneralSettingsForm {
    tabBar.onFocusChanged: {
        if (tabBar.focus) {
            scrollToMiddle(tabBar);
        }
    }

    tabView.onFocusChanged: {
        if (tabView.focus) {
            scrollTo(settingsTabBar);
        }
    }
}
