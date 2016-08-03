import QtQuick 2.3
import QtQuick.Layouts 1.1

import org.couch.itemlist 1.0
import org.couch.filter.movie 1.0

import "../components"

FocusScope {
    id: scope
    focus: true

    property alias delegate: listView.delegate
    property alias items: listView.model
    property alias spacing: listView.spacing
    property real leftMargin: 0
    property real rightMargin: 0
    property bool loading: false
    property int orientation: ListView.Horizontal

    Item {
        id: container
        anchors.fill: parent

        Text {
            anchors.horizontalCenter: listView.horizontalCenter
            anchors.verticalCenter: listView.verticalCenter
            visible: listView.count === 0 && !scope.loading
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

        ListView {
            id: listView
            anchors.fill: parent
            anchors.leftMargin: scope.leftMargin
            anchors.rightMargin: scope.rightMargin
            displayMarginBeginning: scope.leftMargin
            displayMarginEnd: scope.rightMargin

            focus: true
            orientation: scope.orientation

            highlightMoveDuration: 150
            add: addTransition
            footer: Item {
                CouchIndicator {
                    anchors.centerIn: parent
                    visible: scope.loading
                }
            }
        }
    }
}
