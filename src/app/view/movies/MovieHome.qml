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
            delegate: CouchItemDelegate {
                width: bigDelegateWidth
                height: bigDelegateHeight

                placeholder: "../images/placeholder-movie.svg"
                containerColor: highlightColor
                item: modelData
                onClicked: {
                    itemClicked(item);
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
        CouchGridView {
            id: newestList
            leftMargin: listMargin
            rightMargin: listMargin
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredHeight: smallDelegateHeight
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft

            Keys.onUpPressed: {
                popularList.forceActiveFocus();
            }
            MovieFilter {
                id: newestFilter
                order: MovieFilter.Newest
            }

            property var itemList: movies.load(popularFilter)
            loading: itemList.loading
            items: itemList
            cellWidth: smallDelegateWidth
            cellHeight: smallDelegateHeight
            delegate: CouchItemDelegate {
                width: smallDelegateWidth
                height: smallDelegateHeight

                placeholder: "../images/placeholder-movie.svg"
                containerColor: highlightColor
                item: modelData
                onClicked: {
                    itemClicked(modelData);
                }
            }
        }
    }
}
