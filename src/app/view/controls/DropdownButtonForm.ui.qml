import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Templates 2.0 as T

T.ComboBox {
    id: control

    property string text: ""
    property color highlightColor: "green"
    property color color: "white"

    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding + indicator.implicitWidth + 5

    bottomPadding: 10
    rightPadding: 10
    leftPadding: 10
    topPadding: 10

    font.pointSize: 12

    delegate: ItemDelegate {
        width: control.popup.width
        text: modelData
        font.weight: control.currentIndex === index ? Font.DemiBold : Font.Normal
        highlighted: control.highlightedIndex == index
    }

    contentItem: Text {
        id: text

        text: control.text
        font: control.font
        color: control.color
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        id: underline

        anchors.bottom: control.bottom

        height: 2
        color: control.color
    }

    indicator: Image {
        id: indicator

        y: control.topPadding + (control.availableHeight - height) / 2
        x: control.width - implicitWidth - control.rightPadding
        opacity: !control.enabled ? 0.5 : 1.0
        source: "../images/drop-indicator.svg"
        height: 4
        fillMode: Image.PreserveAspectFit
    }

    popup: T.Popup {
        y: control.height - (control.visualFocus ? 0 : 1)
        x: control.width - width
        width: 180
        implicitHeight: contentItem.implicitHeight
        topMargin: 6
        bottomMargin: 6

        contentItem: ListView {
            id: listview
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            highlightRangeMode: ListView.ApplyRange
            highlightMoveDuration: 0

            Rectangle {
                z: 10
                parent: listview
                width: listview.width
                height: listview.height
                color: "transparent"
                border.color: "#bdbebf"
            }

            T.ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle { }
    }

    states: [
        State {
            name: "focused"
            when: control.activeFocus
            PropertyChanges {
                target: underline
                height: 5
                color: control.highlightColor
            }
        }
    ]
}
