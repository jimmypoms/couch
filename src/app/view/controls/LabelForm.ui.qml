import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Label {
    id: control

    property bool secondary: false
    property bool hint: false
    property real primaryOpacity: Material.theme === Material.Light ? 0.87 : 1
    property real secondaryOpacity: Material.theme === Material.Light ? 0.54 : 0.7
    property real hintOpacity: Material.theme === Material.Light ? 0.38 : 0.5

    opacity: control.hint ?
                control.hintOpacity : control.secondary ?
                control.secondaryOpacity : control.primaryOpacity
}
