#include "movie.h"

#include "moviemetadata.h"

#include "../model/source.h"

#include <qstring.h>

Movie::Movie(QObject* parent) :
        Item(parent), m_trailerSource(nullptr)
{
}

Source* Movie::trailerSource()
{
    if (!m_trailerSource && !metadata()->trailer().isEmpty()) {
        m_trailerSource = new Source(this);
        m_trailerSource->setName(name() + " - Trailer");
        m_trailerSource->setUrl(metadata()->trailer());
    }
    return m_trailerSource;
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

MovieMetadata* Movie::metadata() const
{
    return static_cast<MovieMetadata*>(Item::metadata());
}
