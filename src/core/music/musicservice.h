/*
 * musicservice.h
 *
 *  Created on: 10 Feb 2016
 *      Author: jimmypoms
 */

#ifndef MUSICSERVICE_H_
#define MUSICSERVICE_H_

#include "artistmetadata.h"

#include <qobjectdefs.h>
#include <qstring.h>

#include "../couch/cycliccache.h"
#include "../model/service.h"

class CouchActionList;
class CouchItemList;
class MusicFilter;
class Artist;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MusicService : public Service
{
Q_OBJECT

private:
    CyclicCache<QString, ArtistMetadata> m_metadataCache;

    Item* createItem(const Source *source);

public:
    explicit MusicService(QObject *parent = 0);
    virtual ~MusicService() = default;

    Q_INVOKABLE
    CouchItemList *load(MusicFilter *filter);

    Q_INVOKABLE
    CouchItemList *loadItem(Artist *artist);

    Q_INVOKABLE
    CouchActionList *actions(Artist *artist);
};

#endif /* MUSICSERVICE_H_ */
