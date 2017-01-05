#include "moviefilter.h"

MovieFilter::MovieFilter(QObject *parent) :
        Filter(parent), m_genre(Movie::Genre::All)
{
}

Movie::Genre MovieFilter::genre() const
{
    return m_genre;
}

void MovieFilter::setGenre(Movie::Genre genre)
{
    if (m_genre != genre) {
        m_genre = genre;
        setDirty(true);
        Q_EMIT genreChanged();
    }
}
