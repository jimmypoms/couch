import QtQuick 2.4

SettingsList {
    property variant provider: QtObject {}

    settings: provider.settings
}
