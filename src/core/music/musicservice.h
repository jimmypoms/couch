/*
 * musicservice.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef MUSICSERVICE_H_
#define MUSICSERVICE_H_

#include "artist.h"
#include "artistmetadata.h"
#include "musicfilter.h"

#include "couch/cycliccache.h"
#include "couch/service.h"

#include <qlist.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <memory>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MusicService : public Service<Artist, MusicFilter>
{
Q_OBJECT

private:
    CyclicCache<QString, ArtistMetadata> m_metadataCache;

    Artist* createItem(const Source *source);
    CouchActionList* serviceActions(Artist *artist);

protected:
    QList<std::shared_ptr<Item> >::const_iterator findItem(Source* source);

public:
    explicit MusicService(QObject *parent = 0);
    virtual ~MusicService() = default;

    Q_INVOKABLE
    CouchItemList *load(MusicFilter *filter)
    {
        return Service<Artist, MusicFilter>::load(filter);
    }

    Q_INVOKABLE
    CouchItemList *loadItem(Artist *item)
    {
        return Service<Artist, MusicFilter>::load(item);
    }

    Q_INVOKABLE
    CouchActionList *actions(Artist *item)
    {
        return Service<Artist, MusicFilter>::actions(item);
    }
};

#endif /* MUSICSERVICE_H_ */
