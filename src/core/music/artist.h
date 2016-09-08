/*
 * artist.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef ARTIST_H_
#define ARTIST_H_

#include "couch/couchitemlist.h"
#include "couch/item.h"

#include <qlist.h>
#include <qobjectdefs.h>
#include <qurl.h>

class ArtistMetadata;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Artist : public Item
{
Q_OBJECT

Q_PROPERTY(CouchItemList* albums READ albums NOTIFY albumsChanged)
Q_PROPERTY(QList<QUrl> albumCovers READ albumCovers NOTIFY albumCoversChanged)

Q_SIGNALS:
    void albumsChanged();
    void albumCoversChanged();

private:
    SortedCouchItemList m_albums;

public:
    explicit Artist(QObject *parent);
    virtual ~Artist() = default;

    void addSource(const QObject* provider, Source* source);

    ArtistMetadata *metadata() const;
    QList<QUrl> albumCovers() const;

    CouchItemList *albums();
};

#endif /* ARTIST_H_ */
