#ifndef PROVIDERINTERFACE_H_
#define PROVIDERINTERFACE_H_

#include <qobject.h>

#include "../movie/movie.h"
#include "../movie/moviefilter.h"

class CouchSourceList;
class QString;

template<class Item, class Filter>
class Provider
{
public:
    Provider() = default;
    virtual ~Provider() = default;

    virtual const QString &name() const = 0;

    virtual CouchSourceList* load(Filter *filter) = 0;
    virtual CouchSourceList* load(Item* item) = 0;
};

typedef Provider<Movie, MovieFilter> MovieProviderInterface;
Q_DECLARE_INTERFACE(MovieProviderInterface, "org.couch.provider.movie")

#endif /* PROVIDERINTERFACE_H_ */
