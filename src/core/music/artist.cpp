/*
 * artist.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "artist.h"

#include "album.h"
#include "trackmetadata.h"

#include <model/source.h>
#include <qobject.h>
#include <qstring.h>
#include <algorithm>
#include <memory>

Artist::Artist(QObject *parent) :
        Item(parent)
{
    m_albums.setParent(this);
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
    auto it = std::find_if(m_albums.cbegin(), m_albums.cend(),
            [albumName](const std::shared_ptr<Item> &item) {
                auto album = std::static_pointer_cast<Album>(item);
                return album->name() == albumName;
            });
    if (it == m_albums.cend()) {
        std::shared_ptr<Album> album(new Album(this));
        album->setName(albumName);
        album->setMetadata(std::shared_ptr<ItemMetadata>(new AlbumMetadata()));
        m_albums.append(album);
        album->addSource(provider, source);
    } else {
        (*it)->addSource(provider, source);
    }
}

QList<QUrl> Artist::albumCovers() const
{
    QList<QUrl> list;
    const int count = m_albums.rowCount();

    for (int i = 0; i < count; ++i) {
        auto album = std::static_pointer_cast<Album>(m_albums.itemAt(i));
        if (!album->cover().isEmpty()) {
            list.append(album->cover());
        }
    }

    return list;
}

CouchItemList *Artist::albums()
{
    return &m_albums;
}
