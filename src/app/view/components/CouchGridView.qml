import QtQuick 2.2
import QtQuick.Layouts 1.1

import "../components"

FocusScope {
    id: scope
    focus: true

    property alias delegate: gridView.delegate
    property alias cellWidth: gridView.cellWidth
    property alias cellHeight: gridView.cellHeight
    property alias items: gridView.model
    property real leftMargin: 0
    property real rightMargin: 0
    property bool loading: false

    Item {
        id: container
        anchors.fill: parent
        clip: true

        Text {
            anchors.centerIn: parent
            visible: gridView.count == 0 && !scope.loading
            text: qsTr("no results found")

            color: "white"
            font.weight: Font.Light
            font.pointSize: fp(9)
        }

        Transition {
            id: addTransition
            property int position: ViewTransition.index - ViewTransition.targetIndexes[0]
            PropertyAction {
                property: "opacity"
                value: 0
            }
            SequentialAnimation {
                PauseAnimation {
                    duration: addTransition.position * 100
                }
                NumberAnimation {
                    property: "opacity"
                    from: 0
                    to: 1.0
                    duration: 250
                    easing.type: Easing.OutBack
                }
            }
        }

        GridView {
            id: gridView
            anchors.fill: parent
            anchors.leftMargin: scope.leftMargin
            anchors.rightMargin: scope.rightMargin

            focus: true

            populate: addTransition
            add: addTransition
            footer: Item {
                anchors.left: parent.left
                anchors.right: parent.right
                CouchIndicator {
                    anchors.topMargin: dp(10)
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: scope.loading
                }
            }
        }
    }
}
