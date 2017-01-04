import QtQuick 2.7
import Couch 1.0

QtObject {
    id: object

    property Artist tool: Artist {
        id: tool
        name: "Tool"
        metadata: ArtistMetadata {
            name: "Tool"
            image: "http://www.metalinjection.net/wp-content/uploads/2014/07/tool.jpg"
        }
        Album {
            name: "Undertow"
            metadata: AlbumMetadata {
                album: "Undertow"
                genres: [
                    Album.Rock
                ]
            }
            Track {
                metadata: TrackMetadata {
                    trackPosition: 1
                    track: "Intolerance"
                }
            }
            Track {
                metadata: TrackMetadata {
                    trackPosition: 2
                    track: "Prison Sex"
                }
            }
            Track {
                metadata: TrackMetadata {
                    trackPosition: 3
                    track: "Sober"
                }
            }
            Track {
                metadata: TrackMetadata {
                    trackPosition: 4
                    track: "Bottom"
                }
            }
            Track {
                metadata: TrackMetadata {
                    trackPosition: 5
                    track: "Crawl Away"
                }
            }
            Track {
                metadata: TrackMetadata {
                    trackPosition: 6
                    track: "Swamp Song"
                }
            }
            Track {
                metadata: TrackMetadata {
                    trackPosition: 7
                    track: "Undertow"
                }
            }
            Track {
                metadata: TrackMetadata {
                    trackPosition: 8
                    track: "4°"
                }
            }
            Track {
                metadata: TrackMetadata {
                    trackPosition: 9
                    track: "Flood"
                }
            }
            Track {
                metadata: TrackMetadata {
                    trackPosition: 10
                    track: "[silence]"
                }
            }
        }
        Album {
            name: "Salival"
            metadata: AlbumMetadata {
                album: "Salival"
                genres: [
                    Album.Rock
                ]
            }
        }
    }
    property Artist agnesObel: Artist {
        id: agnesObel
        name: "Agnes Obel"
        metadata: ArtistMetadata {
            name: "Agnes Obel"
            image: "https://upload.wikimedia.org/wikipedia/en/d/d7/Agnes-Obel-Aventine.jpg"
        }
        Album {
            metadata: AlbumMetadata {
                genres: [
                    Album.Blues
                ]
            }
        }
    }
    property Artist ninaSimone: Artist {
        id: ninaSimone
        name: "Nina Simone"
        metadata: ArtistMetadata {
            name: "Nina Simone"
        }
        Album {
            metadata: AlbumMetadata {
                genres: [
                    Album.Jazz
                ]
            }
        }
    }
    property variant artists: [
        tool,
        agnesObel,
        ninaSimone
    ]

    function load(filterOrItem) {
        if (filterOrItem.toString().indexOf("Filter") !== -1) {
            return loadFilter(filterOrItem);
        } else {
            return loadItem(filterOrItem);
        }
    }

    function loadFilter(filter) {
        var artists = object.artists;

        if (filter.genre != Album.All) {
            return artists.filter(function(a) {
                var albums = a.albums;
                for (var i=0; i<a.items.length; ++i) {
                    var album = a.items[i];
                    if (album && album.metadata.genres.indexOf(filter.genre.toString()) != -1) {
                        return true;
                    }
                }
                return false;
            });
        }
        if (filter.text) {
            return artists.filter(function(a) {
                if (a.metadata.name.toLowerCase().indexOf(filter.text.toLowerCase()) != -1) {
                    return true;
                }
                return false;
            });
        }

        return artists;
    }

    function loadItem(item) {
    }
}
