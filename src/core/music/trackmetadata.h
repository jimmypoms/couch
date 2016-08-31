/*
 * trackmetadata.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#ifndef TRACKMETADATA_H_
#define TRACKMETADATA_H_

#include "albummetadata.h"

#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT TrackMetadata : public AlbumMetadata
{
Q_OBJECT

Q_PROPERTY(QString track READ track WRITE setTrack NOTIFY trackChanged)
Q_PROPERTY(int trackPosition READ trackPosition WRITE setTrackPosition NOTIFY trackPositionChanged)

Q_SIGNALS:
    void trackChanged();
    void trackPositionChanged();

private:
    QString m_track;
    int m_trackPosition;

public:
    explicit TrackMetadata(QObject *parent = 0);
    virtual ~TrackMetadata() = default;

    const QString &track() const;
    void setTrack(const QString& track);

    int trackPosition() const;
    void setTrackPosition(int trackPosition);

    virtual bool lessThan(const ItemMetadata *other) noexcept
    {
        const TrackMetadata *track = qobject_cast<const TrackMetadata*>(other);
        if (track) {
            return lessThan(track);
        }

        return AlbumMetadata::lessThan(other);
    }

    bool lessThan(const TrackMetadata *other) noexcept
    {
        return trackPosition() < other->trackPosition();
    }
};

#endif /* TRACKMETADATA_H_ */
