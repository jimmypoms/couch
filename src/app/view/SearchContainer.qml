import QtQuick 2.4

SearchContainerForm {
    id: component

    implicitHeight: Math.max(content.implicitHeight, searchResult.implicitHeight)
    implicitWidth: Math.max(content.implicitWidth, searchResult.implicitWidth)

    Binding {
        target: content
        property: "width"
        value: component.width
    }
    Binding {
        target: content
        property: "height"
        value: component.height
    }

    Binding {
        target: searchResult
        property: "width"
        value: component.width
    }
    Binding {
        target: searchResult
        property: "height"
        value: component.height
    }

    Binding {
        target: content
        property: "opacity"
        value: component.searchBar.active ? 0 : 1
    }
    Binding {
        target: searchResult
        property: "opacity"
        value: component.searchBar.active ? 1 : 0
    }

    Binding {
        target: searchResult
        property: "searchText"
        value: component.searchBar.text
    }
    Binding {
        target: searchResult
        property: "service"
        value: component.service
    }
    Binding {
        target: searchResult
        property: "filter"
        value: component.filter
    }

    Keys.onEscapePressed: {
        if (searchBar.activeSearch) {
            searchBar.text = "";
            content.focus = true;
        } else {
            event.accepted = false;
        }
    }

    onSearchResultChanged: {
        searchResult.searchList.itemClicked.connect(content.openDetail);
    }

    onFocusChanged: {
        if (searchBar.active) {
            searchResult.focus = focus;
        } else {
            content.focus = focus;
        }
    }
}
