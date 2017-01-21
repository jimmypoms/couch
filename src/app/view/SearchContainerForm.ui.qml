import QtQuick 2.4
import QtQuick.Layouts 1.3

import "components"

FocusScope {
    id: component

    property SearchResult searchResult
    property Master content
    property SearchBar searchBar
    property variant service
    property variant filter

    children: [
        content,
        searchResult
    ]
}
