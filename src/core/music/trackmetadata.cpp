/*
 * trackmetadata.cpp
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#include "trackmetadata.h"

#include <qobjectdefs.h>
#include <qstring.h>

TrackMetadata::TrackMetadata(QObject *parent) :
        AlbumMetadata(parent)
{
}

QString TrackMetadata::artist() const
{
    return ArtistMetadata::name();
}

void TrackMetadata::setArtist(const QString& a)
{
    if (a != artist()) {
        Q_EMIT artistChanged();
        ArtistMetadata::setName(a);
    }
}

QString TrackMetadata::album() const
{
    return AlbumMetadata::name();
}

void TrackMetadata::setAlbum(const QString& a)
{
    if (a != album()) {
        Q_EMIT albumChanged();
        AlbumMetadata::setName(a);
    }
}
