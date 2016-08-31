/*
 * album.h
 *
 *  Created on: 14 Feb 2016
 *      Author: jimmypoms
 */

#ifndef ALBUM_H_
#define ALBUM_H_

#include "couch/couchitemlist.h"
#include "couch/item.h"

#include <qobjectdefs.h>
#include <qurl.h>

class Artist;
class CouchItemListSortProxy;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Album : public Item
{
Q_OBJECT

Q_ENUMS(Genre)
Q_PROPERTY(QUrl cover READ cover NOTIFY coverChanged)
Q_PROPERTY(CouchItemList* tracks READ tracks NOTIFY tracksChanged)

Q_SIGNALS:
    void coverChanged();
    void tracksChanged();

private:
    QUrl m_cover;
    CouchItemList m_tracks;

public:
    enum Genre
    {
        All,
        Blues,
        Jazz,
        Funk,
        Pop,
        Rock,
        Clasical,
        Heavy,
        Punk,
        Indie,
        Alternative,
        Soul,
        RnB,
        HipHop,
        Rap,
        Country,
        Folk,
        Latin,
        House,
        Dance,
        Raggae,
    };

    explicit Album(Artist *parent);
    virtual ~Album() = default;

    QUrl cover() const;
    void addSource(const QObject* provider, Source* source);

    CouchItemList* tracks();

    Q_INVOKABLE
    CouchItemListSortProxy *tracksSortedByTrackPosition();

    static QString genreToString(Album::Genre genre);
};

#endif /* ALBUM_H_ */
