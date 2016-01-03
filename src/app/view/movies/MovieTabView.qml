import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

import org.couch.filter.movie 1.0
import org.couch.item.movie 1.0

import "../components"

CouchTabView {
    id: movieTabview
    tabbarBackgroundColor: highlightColor
    tabbarSelectedColor: highlightColor
    tabbarBackground: Rectangle {
        anchors.fill: parent
        color: highlightColor
        opacity: highlightOpacity
    }
    property MovieFilter searchFilter: MovieFilter {}
    property bool reloadActive: false

    leftCorner: CouchSearchBox {
        focus: true
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        color: styleData.selected ? tabbarSelectedColor : "transparent"
        onAccepted: {
            searchFilter.text = text;
        }
    }
    leftCornerContent: MovieGrid {
        filter: searchFilter
        autoload: false
        onItemClicked: {
            movieTabview.itemClicked(item);
        }
        Connections {
            target: filter
            onTextChanged: {
                itemList = movies.load(searchFilter)
            }
        }
    }

    signal itemClicked(variant item)

    CouchTab {
        title: "home"
        MovieHome {
            onItemClicked: {
                movieTabview.itemClicked(item);
            }
        } 
    }
    CouchTab {
        title: "action"
        MovieGrid {
            filter: MovieFilter {
                genre: Movie.Action
            }
            onItemClicked: {
                movieTabview.itemClicked(item);
            }
        }
    }
    CouchTab {
        title: "comedy"
        MovieGrid {
            filter: MovieFilter {
                genre: Movie.Comedy
            }
            onItemClicked: {
                movieTabview.itemClicked(item);
            }
        }
    }
    CouchTab {
        title: "drama"
        MovieGrid {
            filter: MovieFilter {
                genre: Movie.Drama
            }
            onItemClicked: {
                movieTabview.itemClicked(item);
            }
        }
    }
    CouchTab {
        title: "romance"
        MovieGrid {
            filter: MovieFilter {
                genre: Movie.Romance
            }
            onItemClicked: {
                movieTabview.itemClicked(item);
            }
        }
    }
    CouchTab {
        title: "fantasy"
        MovieGrid {
            filter: MovieFilter {
                genre: Movie.Fantasy
            }
            onItemClicked: {
                movieTabview.itemClicked(item);
            }
        }
    }
    CouchTab {
        title: "sci-fi"
        MovieGrid {
            filter: MovieFilter {
                genre: Movie.SciFi
            }
            onItemClicked: {
                movieTabview.itemClicked(item);
            }
        }
    }
    CouchTab {
        title: "horror"
        MovieGrid {
            filter: MovieFilter {
                genre: Movie.Horror
            }
            onItemClicked: {
                movieTabview.itemClicked(item);
            }
        }
    }
    CouchTab {
        title: "docu"
        MovieGrid {
            filter: MovieFilter {
                genre: Movie.Documentary
            }
            onItemClicked: {
                movieTabview.itemClicked(item);
            }
        }
    }
}
