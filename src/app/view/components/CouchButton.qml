import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Button {
    id: button
    property color color: "transparent"
    property color focusColor: "grey"
    property color fontColor: "white"
    property int fontPointSize: fp(10)
    property int fontWeight: Font.Normal

    style: ButtonStyle {
        background: Rectangle {
            color: button.activeFocus ? button.focusColor : button.color
        }
        label: Item {
            implicitWidth: row.implicitWidth
            implicitHeight: row.implicitHeight
            baselineOffset: row.y + text.y + text.baselineOffset
            Row {
                id: row
                anchors.centerIn: parent
                spacing: 2
                Image {
                    source: control.iconSource
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    id: text
                    renderType: Text.NativeRendering
                    anchors.verticalCenter: parent.verticalCenter
                    color: button.fontColor
                    font.weight: button.fontWeight
                    font.pointSize: button.fontPointSize
                    text: control.text
                }
            }
        }
    }

    Keys.onReturnPressed: {
        button.clicked();
    }
    Keys.onEnterPressed: {
        button.clicked();
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {
            parent.forceActiveFocus();
        }
        onClicked: {
            parent.clicked();
        }
    }
}
