#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

#include "movie.h"
#include "moviefilter.h"
#include "moviemetadata.h"

#include <qobjectdefs.h>
#include <qstring.h>

#include "../couch/cycliccache.h"
#include "../model/service.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MovieService : public Service<Movie, MovieFilter>
{
Q_OBJECT

private:
    CyclicCache<QString, MovieMetadata> m_metadataCache;

    Movie* createItem(const Source *source);
    CouchActionList* serviceActions(Movie *movie);

public:
    explicit MovieService(QObject *parent = 0);
    virtual ~MovieService() = default;

    Q_INVOKABLE
    CouchItemList *load(MovieFilter *filter)
    {
        return Service<Movie, MovieFilter>::load(filter);
    }

    Q_INVOKABLE
    CouchItemList *loadItem(Movie *item)
    {
        return Service<Movie, MovieFilter>::load(item);
    }

    Q_INVOKABLE
    CouchActionList *actions(Movie *item)
    {
        return Service<Movie, MovieFilter>::actions(item);
    }
};

#endif // MOVIESERVICE_H
