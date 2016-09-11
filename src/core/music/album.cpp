/*
 * album.cpp
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#include "album.h"

#include "artist.h" // IWYU pragma: keep
#include "track.h"
#include "trackmetadata.h"

#include "couch/source.h"

#include <qlist.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qstring.h>
#include <algorithm>
#include <memory>

Album::Album(Artist *parent) :
        Item(parent)
{
    m_tracks.setParent(this);
}

QUrl Album::cover() const
{
    return m_cover;
}

void Album::addSource(const QObject* provider, Source* source)
{
    TrackMetadata *metadata = qobject_cast<TrackMetadata*>(source->itemMetadata());
    QString trackName = metadata->track();
    auto it = std::find_if(m_tracks.cbegin(), m_tracks.cend(),
            [trackName](const std::shared_ptr<Item> &item) {
                auto track = std::static_pointer_cast<Track>(item);
                return track->name() == trackName;
            });
    if (it == m_tracks.cend()) {
        std::shared_ptr<Item> track(new Track(this));
        track->setName(trackName);
        track->setMetadata(std::shared_ptr<ItemMetadata>(new TrackMetadata()));
        track->addSource(provider, source);
        m_tracks.append(track);
    } else {
        (*it)->addSource(provider, source);
    }
    if (m_cover.isEmpty() && !metadata->albumCover().isEmpty()) {
        m_cover = metadata->albumCover();
        Q_EMIT coverChanged();
    }
}

CouchItemList* Album::tracks()
{
    return &m_tracks;
}

CouchItemList* Album::childItems()
{
    return &m_tracks;
}

QString Album::genreToString(Album::Genre genre)
{
    switch (genre) {
        case Genre::All:
            return "all";
        case Genre::Blues:
            return "blues";
        case Genre::Jazz:
            return "jazz";
        case Genre::Funk:
            return "funk";
        case Genre::Pop:
            return "pop";
        case Genre::Rock:
            return "rock";
        case Genre::Clasical:
            return "clasical";
        case Genre::Heavy:
            return "heavy";
        case Genre::Punk:
            return "punk";
        case Genre::Indie:
            return "indie";
        case Genre::Alternative:
            return "alternative";
        case Genre::Soul:
            return "soul";
        case Genre::RnB:
            return "r&b";
        case Genre::HipHop:
            return "hip-hop";
        case Genre::Rap:
            return "rap";
        case Genre::Country:
            return "country";
        case Genre::Folk:
            return "folk";
        case Genre::Latin:
            return "latin";
        case Genre::House:
            return "house";
        case Genre::Dance:
            return "dance";
        case Genre::Raggae:
            return "raggae";
    }
    return "unknown";
}
