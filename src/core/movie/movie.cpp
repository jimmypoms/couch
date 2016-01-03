#include "movie.h"

#include <qstring.h>

Movie::Movie(Service* service) :
        Item(service)
{
}

QString Movie::genreToString(Genre genre)
{
    switch (genre) {
        case Genre::Action:
            return "action";
        case Genre::All:
            return "all";
        case Genre::Comedy:
            return "comedy";
        case Genre::Drama:
            return "drama";
        case Genre::Fantasy:
            return "fantasy";
        case Genre::Romance:
            return "romance";
        case Genre::SciFi:
            return "fiction";
        case Genre::Horror:
            return "horror";
        case Genre::Documentary:
            return "documentary";
    }
    return "unknown";
}
