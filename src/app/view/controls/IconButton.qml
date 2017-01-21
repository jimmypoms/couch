import QtQuick 2.4

IconButtonForm {
    id: control

    Binding {
        target: background
        property: "radius"
        value: control.width / 2
    }
}
