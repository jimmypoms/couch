import QtQuick 2.4

SearchResultForm {
    onSearchTextChanged: {
        filter.text = searchText;
        searchList.contentX = 0;
        if (searchText) {
            searchList.model = service.load(filter);
        } else {
            searchList.model = null;
        }
    }

    Behavior on opacity {
        OpacityAnimator {
            duration: 100
        }
    }
}
