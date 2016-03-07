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
#include <memory>

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
    QString albumName(metadata->album());
    auto it = std::find_if(m_albums.cbegin(), m_albums.cend(), [albumName](Album* album) {
        return album->name() == albumName;
    });
    Album *album;
    if (it == m_albums.cend()) {
        album = new Album(this);
        album->setName(albumName);
        album->setMetadata(std::shared_ptr<ItemMetadata>(new AlbumMetadata()));
        m_albums.append(album);
        Q_EMIT albumsChanged();
        Q_EMIT albumCoversChanged();
    } else {
        album = *it;
    }
    album->addSource(provider, source);
}

QList<QUrl> Artist::albumCovers() const
{
    QList<QUrl> list;
    for (Album *album : m_albums) {
        if (!album->cover().isEmpty()) {
            list.append(album->cover());
        }
    }
    return list;
}

QList<Album*> Artist::albums() const
{
    return m_albums;
}
