import QtQuick 2.4
import QtQuick.Layouts 1.3
import "controls"
import "music"

FocusScope {
    id: content

    property real lineHeight: 40
    property alias tabBar: contentTabBar
    property alias tabView: contentTabView
    property alias flickable: flickable

    Flickable {
        id: flickable

        anchors.fill: parent
        clip: true
        flickableDirection: Flickable.VerticalFlick
        contentHeight: contentTabBar.anchors.topMargin + contentTabBar.height + contentTabView.height

        TabBar {
            id: contentTabBar

            focus: true
            anchors.left: parent.left
            currentIndex: 0
            anchors.top: parent.top
            anchors.topMargin: content.lineHeight * 3
            height: lineHeight

            KeyNavigation.down: contentTabView

            TabButton {
                text: qsTr("Music")
            }
            TabButton {
                text: qsTr("Radio")
            }
        }

        TabView {
            id: contentTabView

            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: contentTabBar.bottom
            currentIndex: contentTabBar.currentIndex

            KeyNavigation.up: contentTabBar

            Music {
                anchors.fill: parent
                lineHeight: content.lineHeight
            }
        }
    }
}

