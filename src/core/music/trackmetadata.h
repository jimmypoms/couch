/*
 * trackmetadata.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#ifndef TRACKMETADATA_H_
#define TRACKMETADATA_H_

#include "albummetadata.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT TrackMetadata : public AlbumMetadata
{
Q_OBJECT

Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged)
Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged)

Q_SIGNALS:
    void artistChanged();
    void albumChanged();

public:
    explicit TrackMetadata(QObject *parent = 0);
    virtual ~TrackMetadata() = default;

    QString artist() const;
    void setArtist(const QString& artist);

    QString album() const;
    void setAlbum(const QString& album);
};

#endif /* TRACKMETADATA_H_ */
