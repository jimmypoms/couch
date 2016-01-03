import QtQuick 2.2
import QtQuick.Layouts 1.1

import org.couch.filter.movie 1.0
import org.couch.item.movie 1.0

import "../components"

FocusScope {
    id: home
    anchors.fill: parent

    property real listMargin: home.width * 0.02
    property real bigDelegateWidth: home.width * 0.16
    property real bigDelegateHeight: bigDelegateWidth * 1.2
    property real smallDelegateWidth: home.width * (0.96/9)
    property real smallDelegateHeight: smallDelegateWidth

    signal itemClicked(variant item)

    ColumnLayout {
        height: parent.height
        width: parent.width
        spacing: dp(20)

        Text {
            text: qsTr("popular")
            color: "white"
            font.weight: Font.Light
            font.pointSize: fp(10)

            Layout.fillWidth: true
            Layout.preferredHeight: dp(40)
            Layout.leftMargin: dp(5)
            Layout.topMargin: dp(5)
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
        }
        CouchListView {
            id: popularList
            focus: true
            leftMargin: listMargin
            rightMargin: listMargin
            Layout.fillWidth: true
            Layout.preferredHeight: bigDelegateHeight
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft

            Keys.onDownPressed: {
                newestList.forceActiveFocus();
            }
            MovieFilter {
                id: popularFilter
                order: MovieFilter.Popular
            }

            property var itemList: movies.load(popularFilter)
            loading: itemList.loading
            items: itemList
            delegate: MovieDelegateBig {
                width: bigDelegateWidth
                height: bigDelegateHeight
                z: activeFocus ? 2 : 1
                onClicked: {
                    itemClicked(modelData);
                }
                Keys.onEnterPressed: {
                    itemClicked(modelData);
                }
                Keys.onReturnPressed: {
                    itemClicked(modelData);
                }
            }
        }

        Text {
            text: qsTr("newest")
            color: "white"
            font.weight: Font.Light
            font.pointSize: fp(10)

            Layout.fillWidth: true
            Layout.preferredHeight: dp(40)
            Layout.leftMargin: dp(5)
            Layout.topMargin: dp(5)
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
        }
        CouchListView {
            id: newestList
            leftMargin: listMargin
            rightMargin: listMargin
            Layout.fillWidth: true
            Layout.preferredHeight: smallDelegateHeight
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft

            Keys.onDownPressed: {
                watchlistList.forceActiveFocus();
            }
            Keys.onUpPressed: {
                popularList.forceActiveFocus();
            }
            MovieFilter {
                id: newestFilter
                order: MovieFilter.Newest
            }

            property var itemList: movies.load(newestFilter)
            loading: itemList.loading
            items: itemList
            delegate: MovieDelegateSmall {
                width: smallDelegateWidth
                height: smallDelegateHeight
                z: activeFocus ? 2 : 1
                onClicked: {
                    itemClicked(modelData);
                }
                Keys.onEnterPressed: {
                    itemClicked(modelData);
                }
                Keys.onReturnPressed: {
                    itemClicked(modelData);
                }
            }
        }

        Text {
            text: qsTr("watchlist")
            color: "white"
            font.weight: Font.Light
            font.pointSize: fp(10)

            Layout.fillWidth: true
            Layout.preferredHeight: dp(40)
            Layout.leftMargin: dp(5)
            Layout.topMargin: dp(5)
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
        }
        CouchGridView {
            id: watchlistList
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft

            Keys.onUpPressed: {
                newestList.forceActiveFocus();
            }

            cellWidth: smallDelegateWidth
            cellHeight: smallDelegateHeight
            delegate: MovieDelegateSmall {
                width: GridView.view.cellWidth
                height: GridView.view.cellHeight
                z: activeFocus ? 2 : 1
                onClicked: {
                    itemClicked(modelData);
                }
                Keys.onEnterPressed: {
                    itemClicked(modelData);
                }
                Keys.onReturnPressed: {
                    itemClicked(modelData);
                }
            }
        }
    }
}
