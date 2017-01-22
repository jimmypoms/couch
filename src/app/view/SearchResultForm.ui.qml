import QtQuick 2.4
import QtQuick.Layouts 1.3

import "components"

FocusScope {
    id: component

    property variant service
    property variant filter
    property string searchText
    property alias searchList: searchList
    property string emptyText: qsTr("type to search")
    property string noResultsText: qsTr("no results found")

    ItemListView {
        id: searchList

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        focus: component.focus
        emptyText: searchText.length > 0 ? component.noResultsText : component.emptyText
    }
}
