/*
 * artist.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef ARTIST_H_
#define ARTIST_H_

#include "album.h"

#include <qlist.h>
#include <qobjectdefs.h>
#include <qurl.h>

#include "../model/item.h"

class ArtistMetadata;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Artist : public Item
{
Q_OBJECT

Q_PROPERTY(QList<Album*> albums READ albums NOTIFY albumsChanged)
Q_PROPERTY(QList<QUrl> albumCovers READ albumCovers NOTIFY albumCoversChanged)

Q_SIGNALS:
    void albumsChanged();
    void albumCoversChanged();

private:
    QList<Album*> m_albums;

public:
    explicit Artist(QObject *parent);
    virtual ~Artist() = default;

    void addSource(const QObject* provider, Source* source);

    ArtistMetadata *metadata() const;
    QList<QUrl> albumCovers() const;
    QList<Album*> albums() const;
};

#endif /* ARTIST_H_ */
