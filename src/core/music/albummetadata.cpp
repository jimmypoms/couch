/*
 * albummetadata.cpp
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#include "albummetadata.h"

#include <qlist.h>

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
        m_album = album;
        Q_EMIT albumChanged();
    }
}

const QUrl& AlbumMetadata::albumCover() const
{
    return m_albumCover;
}

void AlbumMetadata::setAlbumCover(const QUrl& albumCover)
{
    if (m_albumCover != albumCover) {
        m_albumCover = albumCover;
        Q_EMIT albumCoverChanged();
    }
}

int AlbumMetadata::trackTotal() const
{
    return m_trackTotal;
}

void AlbumMetadata::setTrackTotal(int trackTotal)
{
    if (m_trackTotal != trackTotal) {
        m_trackTotal = trackTotal;
        Q_EMIT trackTotalChanged();
    }
}
