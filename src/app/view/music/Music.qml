import QtQuick 2.4

import Couch 1.0

MusicForm {
    id: control

    ListModel {
        id: genres
    }

    MusicFilter {
        id: popularFilter
        order: MusicFilter.Popular
    }

    MusicFilter {
        id: genreFilter
        order: MusicFilter.Popular
        genre: genres.get(genreComboBox.currentIndex).genre
    }

    property Component detailComponent: Qt.createComponent("MusicDetail.qml")

    featuredList.model: music.load(popularFilter)
    search.service: music
    search.filter: MusicFilter {
        order: Filter.Popular
    }

    onFocusChanged: {
        if (focus && searchVisible) {
            searchList.focus = true;
        } else if (focus) {
            featuredList.focus = true;
        }
    }

    searchList.onItemClicked: openDetail(item)
    featuredList.onItemClicked: openDetail(item)
    genreList.onItemClicked: openDetail(item)

    searchField.onActiveChanged: {
        if (!searchField.active) {
            searchVisible = false
            if (searchList.focus) {
                featuredList.focus = true;
            }
        }
    }

    Component.onCompleted: {
        initFocusListeners();
        initGenreComboBox();
        initGenreList();
    }

    function openDetail(item) {
        music.loadItem(item);
        loadDetail(detailComponent, {
           lineHeight: control.lineHeight,
           artist: item
        });
    }

    function initFocusListeners() {
        searchList.focusChanged.connect(function() {
            if (searchList.focus) {
                scrollToMiddle(searchField);
            }
        });

        featuredList.focusChanged.connect(function() {
            if (featuredList.focus) {
                if (searchVisibleTransition.running) {
                    scrollToMiddle(searchField);
                } else {
                    scrollToMiddle(featuredList);
                }
            }
        });

        genreComboBox.focusChanged.connect(function() {
            if (genreComboBox.focus) {
                scrollToMiddle(genreList);
            }
        });

        genreList.focusChanged.connect(function() {
            if (genreList.focus) {
                scrollToMiddle(genreList);
            }
        });

        historyList.focusChanged.connect(function() {
            if (historyList.focus) {
                scrollToMiddle(historyList);
            }
        });
    }

    function initGenreComboBox() {
        genres.append({
            text: qsTr("Rock"),
            genre: Album.Rock
        });
        genres.append({
            text: qsTr("Blues"),
            genre: Album.Blues
        });
        genreComboBox.textRole = "text";
        genreComboBox.model = genres;
    }

    function initGenreList() {
        genreFilter.genre = genres.get(genreComboBox.currentIndex).genre;
        genreList.model = music.load(genreFilter);

        genreComboBox.currentIndexChanged.connect(function() {
            genreFilter.genre = genres.get(genreComboBox.currentIndex).genre;
            genreList.model = music.load(genreFilter);
        });
    }

    transitions: [
        Transition {
            id: searchVisibleTransition

            from: ""
            to: "searchVisible"
            reversible: true
            AnchorAnimation {
                duration: 200
            }
        }
    ]
}
