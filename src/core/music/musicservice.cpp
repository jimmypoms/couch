/*
 * musicservice.cpp
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#include "musicservice.h"

#include "trackmetadata.h"

#include "couch/source.h"

#include <qdebug.h>
#include <qlogging.h>
#include <qobject.h>
#include <qurl.h>
#include <algorithm>
#include <unordered_map>

MusicService::MusicService(QObject* parent) :
        Service(parent, "music"), m_metadataCache("music/metadata")
{
}

Artist* MusicService::createItem(const Source* source)
{
    ItemMetadata *metadata = source->itemMetadata();
    TrackMetadata *tm = qobject_cast<TrackMetadata*>(metadata);
    if (!tm || tm->artist().isEmpty() || tm->artist().isNull()) {
        qDebug() << "invalid track metadata of source:" << source->url() << metadata;
        return nullptr;
    }
    Artist *artist = new Artist(this);
    artist->setName(tm->artist());
    QString key = tm->artist();
    auto i = m_metadataCache.find(key);
    if (i != m_metadataCache.end()) {
        artist->setMetadata(i->second);
    } else {
        artist->setMetadata(m_metadataCache.insert(key, new ArtistMetadata()));
        artist->metadata()->setArtist(tm->artist());
    }
    return artist;
}

QList<std::shared_ptr<Item> >::const_iterator MusicService::findItem(Source *source)
{
    return std::find_if(m_items.cbegin(), m_items.cend(),
            [source](std::shared_ptr<Item> item)->bool {
                const ArtistMetadata *a = qobject_cast<const ArtistMetadata*>(item->metadata());
                const TrackMetadata *t = qobject_cast<const TrackMetadata*>(source->itemMetadata());
                return a && t && a->artist() == t->artist();
            });
}

CouchActionList* MusicService::serviceActions(Artist* artist)
{
    return nullptr;
}
