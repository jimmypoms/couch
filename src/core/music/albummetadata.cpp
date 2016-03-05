/*
 * albummetadata.cpp
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#include "albummetadata.h"

AlbumMetadata::AlbumMetadata(QObject *parent) :
        ArtistMetadata(parent)
{
}

const QStringList& AlbumMetadata::genres() const
{
    return m_genres;
}

void AlbumMetadata::setGenres(const QStringList& genres)
{
    if (m_genres != genres) {
        m_genres = genres;
        Q_EMIT genresChanged();
    }
}

void AlbumMetadata::addGenre(const QString& genre)
{
    this->m_genres.append(genre);
    Q_EMIT genresChanged();
}

const QString &AlbumMetadata::album() const
{
    return m_album;
}

void AlbumMetadata::setAlbum(const QString& album)
{
    if (m_album != album) {
        Q_EMIT albumChanged();
        m_album = album;
    }
}
