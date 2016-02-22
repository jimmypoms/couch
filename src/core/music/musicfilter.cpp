/*
 * musicfilter.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "musicfilter.h"

MusicFilter::MusicFilter(QObject *parent) :
        Filter(parent), m_genre(Album::Genre::All)
{
}

Album::Genre MusicFilter::genre() const
{
    return m_genre;
}

void MusicFilter::setGenre(Album::Genre genre)
{
    if (m_genre != genre) {
        m_genre = genre;
        Q_EMIT genreChanged();
    }
}

