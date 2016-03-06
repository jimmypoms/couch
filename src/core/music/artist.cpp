/*
 * artist.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "artist.h"

#include "trackmetadata.h"

#include <model/source.h>
#include <qobject.h>
#include <qstring.h>
#include <algorithm>

Artist::Artist(QObject *parent) :
        Item(parent)
{
}

ArtistMetadata* Artist::metadata() const
{
    return static_cast<ArtistMetadata*>(Item::metadata());
}

void Artist::addSource(const QObject* provider, Source* source)
{
    Item::addSource(provider, source);
    TrackMetadata *metadata = qobject_cast<TrackMetadata*>(source->itemMetadata());
    QString albumTitle = metadata->album();
    auto it = std::find_if(m_albums.cbegin(), m_albums.cend(), [albumTitle](Album* album) {
        return album->title() == albumTitle;
    });
    if (it == m_albums.cend()) {
        Album *album = new Album(this);
        album->setTitle(albumTitle);
        album->setCover(metadata->albumCover());
        m_albums.append(album);
        Q_EMIT albumsChanged();
        Q_EMIT albumCoversChanged();
    }
}

QList<QUrl> Artist::albumCovers() const
{
    QList<QUrl> list;
    for (Album *album : m_albums) {
        list.append(album->cover());
    }
    return list;
}

QList<Album*> Artist::albums() const
{
    return m_albums;
}
