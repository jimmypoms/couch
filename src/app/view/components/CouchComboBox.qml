import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

ComboBox {
    id: comboBox
    property color color: "red"
    property color focusColor: "grey"

    style: ComboBoxStyle {
        background: Rectangle {
            color: comboBox.activeFocus ? comboBox.focusColor : comboBox.color
        }
    }

    onHoveredChanged: {
        if (hovered) {
            comboBox.forceActiveFocus();
        }
    }
}
