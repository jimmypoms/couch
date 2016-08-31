/*
 * albummetadata.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#ifndef ALBUMMETADATA_H_
#define ALBUMMETADATA_H_

#include "artistmetadata.h"

#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qurl.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class AlbumMetadata : public ArtistMetadata
{
Q_OBJECT

Q_PROPERTY(QStringList genres READ genres WRITE setGenres NOTIFY genresChanged)
Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged)
Q_PROPERTY(QUrl albumCover READ albumCover WRITE setAlbumCover NOTIFY albumCoverChanged)
Q_PROPERTY(int trackTotal READ trackTotal WRITE setTrackTotal NOTIFY trackTotalChanged)

Q_SIGNALS:
    void genresChanged();
    void albumChanged();
    void albumCoverChanged();
    void trackTotalChanged();

private:
    QStringList m_genres;
    QString m_album;
    QUrl m_albumCover;
    int m_trackTotal;

public:
    explicit AlbumMetadata(QObject *parent = 0);
    virtual ~AlbumMetadata() = default;

    const QStringList& genres() const;
    void setGenres(const QStringList& genres);
    void addGenre(const QString& genre);

    const QString &album() const;
    void setAlbum(const QString& album);

    const QUrl &albumCover() const;
    void setAlbumCover(const QUrl &albumCover);

    int trackTotal() const;
    void setTrackTotal(int trackTotal);

    virtual bool lessThan(const ItemMetadata *other) noexcept
    {
        const AlbumMetadata *album = qobject_cast<const AlbumMetadata*>(other);
        if (album) {
            return lessThan(album);
        }

        return ArtistMetadata::lessThan(other);
    }

    bool lessThan(const AlbumMetadata *other) noexcept
    {
        return year() < other->year();
    }
};

#endif /* ALBUMMETADATA_H_ */
