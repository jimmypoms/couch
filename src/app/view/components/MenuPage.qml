import QtQuick 2.4
import QtQuick.Controls.Material 2.0

MenuPageForm {
    Binding {
        target: actionsPane.background
        property: "color"
        value: Material.primary
    }
    Component.onCompleted: {
        list.currentIndex = 0
    }
}
