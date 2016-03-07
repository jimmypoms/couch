/*
 * album.cpp
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#include "album.h"

#include "artist.h"
#include "trackmetadata.h"

#include <model/source.h>
#include <qobject.h>
#include <qstring.h>
#include <algorithm>
#include <memory>

Album::Album(Artist *parent) :
        Item(parent)
{
}

QUrl Album::cover() const
{
    return m_cover;
}

void Album::addSource(const QObject* provider, Source* source)
{
    Item::addSource(provider, source);
    TrackMetadata *metadata = qobject_cast<TrackMetadata*>(source->itemMetadata());
    QString trackName = metadata->track();
    auto it = std::find_if(m_tracks.cbegin(), m_tracks.cend(), [trackName](Track* track) {
        return track->name() == trackName;
    });
    Track *track;
    if (it == m_tracks.cend()) {
        track = new Track(this);
        track->setName(trackName);
        track->setMetadata(std::shared_ptr<ItemMetadata>(new TrackMetadata()));
        m_tracks.append(track);
        Q_EMIT tracksChanged();
    } else {
        track = *it;
    }
    track->addSource(provider, source);
    if (m_cover.isEmpty() && !metadata->albumCover().isEmpty()) {
        m_cover = metadata->albumCover();
        Q_EMIT coverChanged();
    }
}

QList<Track*> Album::tracks() const
{
    return m_tracks;
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
