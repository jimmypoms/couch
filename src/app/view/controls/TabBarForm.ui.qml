import QtQuick 2.7
import QtQuick.Templates 2.0 as T

T.TabBar {
    id: control

    property TabView tabView: TabView {}
    property color color: "white"
    property color highlightColor: "green"
    property int highlightHeight: 2

    spacing: 5

    KeyNavigation.down: tabView

    contentItem: ListView {
        id: list

        implicitWidth: contentWidth
        implicitHeight: 48

        model: control.contentModel
        currentIndex: control.currentIndex

        spacing: control.spacing
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickIfNeeded
        snapMode: ListView.SnapToItem

        highlightMoveDuration: 200
        highlightResizeDuration: 200
        highlightFollowsCurrentItem: true
        highlightRangeMode: ListView.ApplyRange
        preferredHighlightBegin: 48
        preferredHighlightEnd: width - 48

        highlight: Item {
            z: 2
            Rectangle {
                height: highlightHeight
                width: list.currentItem.implicitWidth
                y: control.position === T.TabBar.Footer ? 0 : parent.height - height
                color: control.color
            }
        }
    }

    background: Item {
    }

    states: [
        State {
            name: "focused"
            when: control.activeFocus
            PropertyChanges {
                target: control
                color: control.highlightColor
                highlightHeight: 5
            }
        }
    ]

    signal clicked()
}
