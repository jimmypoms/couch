import QtQuick 2.2

FocusScope {
    id: tabbar
    height: Math.max(tabrow.height, rightCornerLoader.height, leftCornerLoader.height)
    width: tabview.width
    focus: true

    signal leftCornerClicked()
    signal tabbarClicked()

    property var tabview
    property real availableWidth: tabview.width - rightCornerLoader.width - leftCornerLoader.width
    property alias leftCorner: leftCornerLoader.sourceComponent
    property bool fillLeftCorner: false
    property alias rightCorner: rightCornerLoader.sourceComponent
    property Component tabbarDelegate: Rectangle {
        color: "transparent"
        implicitWidth: text.width + dp(10)
        implicitHeight: dp(30)

        Text {
            id: text
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.margins: dp(5)
            text: styleData.title
        }
    }
    property Component tabbarBackground: undefined

    Loader {
        id: leftBackgroundLoader
        anchors.top: tabbar.top
        anchors.bottom: tabbar.bottom
        anchors.right: tabbar.right
        anchors.left: tabrow.right
        sourceComponent: tabbar.tabbarBackground
    }

    Loader {
        id: rightBackgroundLoader
        anchors.top: tabbar.top
        anchors.bottom: tabbar.bottom
        anchors.left: tabbar.left
        anchors.right: tabrow.left
        sourceComponent: tabbar.tabbarBackground
    }

    ListView {
        id: tabrow
        orientation: Qt.Horizontal
        focus: true
        anchors.horizontalCenter: tabbar.horizontalCenter

        // Note this will silence the binding loop warnings caused by QTBUG-35038
        // and should be removed when this issue is resolved.
        property int contentWidthWorkaround: contentWidth > 0 ? contentWidth: 0
        width: Math.min(availableWidth, count ? contentWidthWorkaround : availableWidth)
        height: currentItem ? currentItem.height : 0

        // We cannot bind directly to the currentIndex because the actual model is
        // populated after the listview is completed, resulting in an invalid contentItem
        currentIndex: tabview.currentIndex < model.count ? tabview.currentIndex : -1
        onCurrentIndexChanged: tabrow.positionViewAtIndex(currentIndex, ListView.Contain)

        model: tabview.__tabs

        delegate: MouseArea {
            id: tabitem
            hoverEnabled: true
            enabled: true
            focus: true

            implicitWidth: tabloader.implicitWidth
            implicitHeight: tabloader.implicitHeight

            property var tab: modelData
            property var item: modelData.item
            property string title: modelData.title
            property bool selected: tabview.currentIndex === index
            property int tabindex: index

            Loader {
                id: tabloader

                property QtObject styleData: QtObject {
                    readonly property alias tab: tabitem.tab
                    readonly property alias item: tabitem.item
                    readonly property alias title: tabitem.title
                    readonly property alias selected: tabitem.selected
                    readonly property alias index: tabitem.tabindex
                }

                sourceComponent: tabbarDelegate
            }

            function changeTab() {
                tabbarClicked();
                tabview.currentIndex = index;
            }

            Connections {
                target: tabrow
                onCurrentIndexChanged: {
                    if (tabrow.currentIndex === index) {
                        tabloader.item.forceActiveFocus();
                    }
                }
            }

            onEntered: tabitem.forceActiveFocus()
            onClicked: changeTab()
            Keys.onReturnPressed: changeTab()
            Keys.onEnterPressed: changeTab()
        }

        Keys.onRightPressed: {
            var prevCurrentIndex = tabrow.currentIndex;
            tabrow.incrementCurrentIndex();
            if (prevCurrentIndex !== currentIndex) {
                event.accepted = true;
                return;
            }
            if (rightCornerLoader.item) {
                rightCornerLoader.forceActiveFocus();
                event.accepted = true;
                return;
            }
        }

        Keys.onLeftPressed: {
            var prevCurrentIndex = tabrow.currentIndex;
            tabrow.decrementCurrentIndex();
            if (prevCurrentIndex !== currentIndex) {
                event.accepted = true;
                return;
            }
            if (leftCornerLoader.item) {
                leftCornerLoader.forceActiveFocus();
                event.accepted = true;
                return;
            }
        }
    }

    MouseArea {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        width: leftCornerLoader.item ? leftCornerLoader.item.implicitWidth : 0
        height: leftCornerLoader.item ? leftCornerLoader.item.implicitHeight : 0
        KeyNavigation.right: tabrow
        onEntered: leftCornerLoader.item.forceActiveFocus()
        onClicked: leftCornerClicked()
        Keys.onReturnPressed: leftCornerClicked()
        Keys.onEnterPressed: leftCornerClicked()
        Loader {
            id: leftCornerLoader

            property QtObject styleData: QtObject {
                readonly property bool selected: tabbar.tabview.leftCornerSelected
            }
        }
    }

    Loader {
        id: rightCornerLoader
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        width: item ? item.implicitWidth : 0
        height: item ? item.implicitHeight : 0

        KeyNavigation.left: tabrow
    }
}
