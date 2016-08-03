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

const QString &TrackMetadata::track() const
{
    return m_track;
}

void TrackMetadata::setTrack(const QString& track)
{
    if (m_track != track) {
        m_track = track;
        Q_EMIT trackChanged();
    }
}

int TrackMetadata::trackPosition() const
{
    return m_trackPosition;
}

void TrackMetadata::setTrackPosition(int trackPosition)
{
    if (m_trackPosition != trackPosition) {
        m_trackPosition = trackPosition;
        Q_EMIT trackPositionChanged();
    }
}
