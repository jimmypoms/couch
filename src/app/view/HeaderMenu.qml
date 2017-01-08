import QtQuick 2.4

HeaderMenuForm {
    signal showSettings()

    settingsButton.onClicked: showSettings()
    closeButton.onClicked: Qt.quit()
}
