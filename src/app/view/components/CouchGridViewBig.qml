import QtQuick 2.2
import QtQuick.Layouts 1.1

import "../components"

FocusScope {
    id: scope
    focus: true

    property alias focusColor: focusHighlight.color
    property alias delegate: model.delegate
    property alias items: model.model
    property alias title: header.text
    property bool loading: false

    Item {
        id: container
        anchors.fill: parent

        Rectangle {
            id: focusHighlight
            anchors.fill: parent
            color: "#193441"
            opacity: scope.activeFocus ? 0.5 : 0

            Behavior on opacity {
                NumberAnimation {
                    duration: 200
                }
            }
        }

        Text {
            id: header

            color: "white"
            font.weight: Font.Normal
            font.pointSize: fp(10)
            height: dp(30)

            anchors.top: parent.top
            anchors.topMargin: dp(5)
            anchors.left: parent.left
            anchors.right: parent.right
        }

        CouchIndicator {
            anchors.fill: gridView
            visible: scope.loading
            running: scope.loading
        }

        Text {
            anchors.horizontalCenter: gridView.horizontalCenter
            visible: gridView.count == 0 && !scope.loading
            text: qsTr("no results found")

            color: "white"
            font.weight: Font.Light
            font.pointSize: fp(9)
        }

        FocusScope {
            id: gridView
            anchors.top: header.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            focus: true
            GridLayout {
                property currentIndex: 0
                Repeater {
                    id: model
                }
                onCurrentIndex: {
                    itemAt(currentIndex).forceActiveFocus();
                }
            }
        }
    }
}
