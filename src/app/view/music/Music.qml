import QtQuick 2.4

import Couch 1.0

MusicForm {
    id: control

    ListModel {
        id: genres
        ListElement {
            name: qsTr("Rock")
            genre: Album.Rock
        }
        ListElement {
            name: qsTr("Blues")
            genre: Album.Blues
        }
        ListElement {
            name: qsTr("Jazz")
            genre: Album.Jazz
        }
        ListElement {
            name: qsTr("House")
            genre: Album.House
        }
    }

    MusicFilter {
        id: popularFilter
        order: MusicFilter.Popular
    }

    MusicFilter {
        id: genreFilter
        order: MusicFilter.Popular
        genre: genres.get(genreTabView.currentIndex).genre
    }

    property Component detailComponent: Qt.createComponent("MusicDetail.qml")

    featuredList.onAboutToReachEnd: {
        if (popularFilter.hasMore) {
            popularFilter.offset += popularFilter.limit;
            featuredList.model = music.load(popularFilter);
        }
    }

    genreList.onAboutToReachEnd: {
        if (genreFilter.hasMore) {
            genreFilter.offset += genreFilter.limit;
            genreList.model = music.load(genreFilter);
        }
    }

    onFocusChanged: {
        featuredList.focus = true;
    }

    featuredList.onItemClicked: openDetail(item)
    genreList.onItemClicked: openDetail(item)

    Component.onCompleted: {
        featuredList.model = music.load(popularFilter);
        genreList.model = music.load(genreFilter);

        initFocusListeners();
        initGenreTabView();
        initGenreList();
    }

    function openDetail(item) {
        music.loadItem(item);
        loadDetail(detailComponent, {
            artist: item
        });
    }

    function initFocusListeners() {
        featuredList.activeFocusChanged.connect(function() {
            if (featuredList.focus) {
                scrollToMiddle(featuredList);
            }
        });

        genreTabView.activeFocusChanged.connect(function() {
            if (genreTabView.focus) {
                scrollToMiddle(genreList);
            }
        });

        genreList.activeFocusChanged.connect(function() {
            if (genreList.focus) {
                scrollToMiddle(genreList);
            }
        });
    }

    function initGenreTabView() {
        genreTabViewRepeater.model = genres;
    }

    function initGenreList() {
        genreTabView.currentIndexChanged.connect(function() {
            genreFilter.offset = 0;
            genreFilter.genre = genres.get(genreTabView.currentIndex).genre;
            genreList.model = music.load(genreFilter);
        });
    }
}
