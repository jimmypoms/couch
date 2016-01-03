#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

#include <qobjectdefs.h>
#include <qstring.h>

#include "../couch/cycliccache.h"
#include "../model/service.h"

#include "moviemetadata.h"

class CouchItemList;
class Movie;
class MovieFilter;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MovieService : public Service
{
Q_OBJECT

private:
    CyclicCache<QString, MovieMetadata> m_metadataCache;

    Item* createItem(const Source *source);

public:
    explicit MovieService(QObject *parent = 0);
    virtual ~MovieService() = default;

    Q_INVOKABLE
    CouchItemList *load(MovieFilter *filter);
    Q_INVOKABLE
    CouchItemList *loadItem(Movie *movie);
};

#endif // MOVIESERVICE_H
