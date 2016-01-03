import QtQuick 2.2
import QtQuick.Controls 1.2

FocusScope {
    id: tabview
    focus: true

    implicitWidth: dp(240)
    implicitHeight: dp(150)

    readonly property int count: __tabs.count
    readonly property var tabbar: tabbar
    readonly property alias leftCornerSelected: leftCornerContentLoader.visible
    readonly property alias rightCornerSelected: rightCornerContentLoader.visible

    property alias leftCorner: tabbar.leftCorner
    property alias leftCornerContent: leftCornerContentLoader.sourceComponent
    property alias rightCorner: tabbar.rightCorner
    property alias rightCornerContent: rightCornerContentLoader.sourceComponent
    property alias tabbarDelegate: tabbar.tabbarDelegate
    property alias tabbarBackground: tabbar.tabbarBackground

    property double tabbarButtonWidth: implicitWidth
    property color tabbarFontColor: "white"
    property color tabbarSelectedColor: "#193441"
    property color tabbarBackgroundColor: "#193441"
    property real tabbarSelectedOpacity: 0.5
    property variant tabbarFontWeight: Font.Light
    property double tabbarFontPointSize: fp(9)
    property int currentIndex: 0

    function addTabs(tabs) {
        for (var i = 0; i < tabs.length; ++ i) {
            var tab = tabs[i]
            if (! tab.__inserted && tab.Accessible.role === Accessible.LayeredPane) {
                tab.__inserted = true
                tab.parent = stack
                __tabs.append({
                        tab: tab
                    })
            }
        }
        __updateCurrentIndex()
    }

    function addTab(title, component) {
        return insertTab(__tabs.count, title, component)
    }

    function insertTab(index, title, component) {
        var tab = tabcomp.createObject()
        tab.sourceComponent = component
        tab.title = title
        __tabs.insert(index, {
            tab: tab
        })
        tab.__inserted = true
        tab.parent = stack
        __didInsertIndex(index)
        __updateCurrentIndex()
        return tab
    }

    function currentTab() {
        if (leftCornerContentLoader.visible) {
            return leftCornerContentLoader
        }
        if (rightCornerContentLoader.visible) {
            return rightCornerContentLoader
        }
        return __tabs.get(currentIndex).tab;
    }

    function currentItem() {
        return currentTab().item;
    }

    function hideItems() {
        stack.enabled = false;
        stack.visible = false;
    }

    function showItems() {
        stack.enabled = true;
        stack.visible = true;
    }

    property ListModel __tabs: ListModel {
    }

    onCurrentIndexChanged: __updateCurrentIndex()

    function __didInsertIndex(index) {
        // Make sure currentIndex points to the same tab as before the insertion.
        if (count > 1 && currentIndex >= index)
            currentIndex ++
    }

    function __updateCurrentIndex() {
        for (var i = 0; i < __tabs.count; ++ i) {
            var child = __tabs.get(i).tab
            if (leftCornerContentLoader.visible || rightCornerContentLoader.visible) {
                child.visible = false
            } else {
                child.visible = (i == currentIndex ? true : false)
            }
        }
    }

    CouchTabBar {
        id: tabbar
        focus: true
        z: 1

        height: dp(40)
        anchors.top: tabview.top
        anchors.left: tabview.left
        anchors.right: tabview.right

        tabview: tabview
        Keys.onDownPressed: {
            var item = currentItem();
            if (item.enabled) {
                currentItem().forceActiveFocus();
            }
        }
        tabbarBackground: Rectangle {
            anchors.fill: parent
            color: "#193441"
            opacity: 0.5
        }
        tabbarDelegate: Item {
            width: dp(140)
            height: dp(40)

            Rectangle {
                anchors.fill: parent
                color: tabbarBackgroundColor
                opacity: tabbarSelectedOpacity
            }
            CouchButton {
                id: button
                anchors.fill: parent
                color: styleData.selected ? tabbarSelectedColor : "transparent"

                fontColor: "white"
                fontWeight: Font.Light
                fontPointSize: fp(9)
                text: styleData.title

                onClicked: {
                    leftCornerContentLoader.visible = false
                    rightCornerContentLoader.visible = false
                    tabview.currentIndex = styleData.index;
                }
            }
            onActiveFocusChanged: {
                if (activeFocus) {
                    button.forceActiveFocus();
                }
            }
        }

        onLeftCornerClicked: {
            if (leftCornerContentLoader.item) {
                leftCornerContentLoader.visible = true
                tabview.currentIndex = -1
            }
        }
        onTabbarClicked: {
            leftCornerContentLoader.visible = false
            rightCornerContentLoader.visible = false
        }
    }

    Component {
        id: tabcomp
        CouchTab {
        }
    }

    Item {
        id: stack
        focus: true

        anchors.top: tabbar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Keys.onUpPressed: {
            tabbar.forceActiveFocus();
        }
        Loader {
            id: leftCornerContentLoader
            anchors.fill: parent
            visible: false
        }
        Loader {
            id: rightCornerContentLoader
            anchors.fill: parent
            visible: false
        }
    }

    onChildrenChanged: addTabs(tabview.children)
}
