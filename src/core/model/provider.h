#ifndef PROVIDERINTERFACE_H_
#define PROVIDERINTERFACE_H_

#include "couch/movie/movie.h"
#include "couch/movie/moviefilter.h"
#include "couch/music/artist.h"
#include "couch/music/musicfilter.h"

#include <qlocale.h>
#include <qobject.h>

class QTranslator;

class SettingList;

class CouchSourceList;

template<class Item, class Filter>
class Provider
{
public:
    virtual ~Provider() = default;

    virtual const QString &name() const = 0;
    virtual QString playIcon() const = 0;

    virtual CouchSourceList* load(Filter *filter) = 0;
    virtual CouchSourceList* load(Item* item) = 0;

    virtual SettingList* buildSettings(const SettingList* parent) = 0;
    virtual QTranslator* pluginTranslator(const QLocale &locale) = 0;
};

typedef Provider<Movie, MovieFilter> MovieProviderInterface;
Q_DECLARE_INTERFACE(MovieProviderInterface, "org.couch.provider.movie")

typedef Provider<Artist, MusicFilter> MusicProviderInterface;
Q_DECLARE_INTERFACE(MusicProviderInterface, "org.couch.provider.music")

#endif /* PROVIDERINTERFACE_H_ */
