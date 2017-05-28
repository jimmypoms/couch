/*
 * localmovieprovider.h
 *
 *  Created on: 4 Nov 2015
 *      Author: jimmypoms
 */

#ifndef LOCALMOVIEPROVIDER_H_
#define LOCALMOVIEPROVIDER_H_

#include "moviemetadatafetcher.h"

#include "../common/localprovider.h"
#include "couch/movie/movie.h"
#include "couch/movie/moviefilter.h"
#include "couch/movie/movieprovider.h"
#include "couch/source.h"

#include <qlist.h>
#include <qlocale.h>
#include <qmutex.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <string>

namespace Xapian
{
    class MSet;
    class QueryParser;
    class TermGenerator;
    class WritableDatabase;
} /* namespace Xapian */

class LocalMovieProvider : public MovieProvider, public LocalProvider<Movie, MovieFilter>
{
Q_OBJECT

Q_PLUGIN_METADATA(IID "org.couch.provider.local.movie")
Q_INTERFACES(MovieProviderInterface)

Q_SIGNALS:
    void sourcesReady(const QList<Source*> &sources, const QString &id);

private:
    static const QStringList s_filenameFilters;
    static const std::string s_prefixTitle;
    static const std::string s_prefixTagline;
    static const std::string s_prefixYear;
    static const std::string s_prefixDirector;
    static const std::string s_prefixActor;
    static const std::string s_prefixGenre;

    MovieMetadataFetcher m_metadataFetcher;
    QMutex m_mutex;

    void searchFinished(const Xapian::MSet &matches, const QString &id);

    QStringList filenameFilters() const;
    Xapian::Query buildQuery(Xapian::QueryParser &qp, const Movie *item);
    Xapian::Query buildQuery(Xapian::QueryParser &qp, const MovieFilter *filter);
    void indexFile(Xapian::WritableDatabase &writer, Xapian::TermGenerator &indexer,
            Source &source);

public:
    explicit LocalMovieProvider(QObject* parent = 0);
    virtual ~LocalMovieProvider() = default;

    QString playIcon() const;
    SettingList *buildSettings(const SettingList* parent = 0);
    QTranslator *pluginTranslator(const QLocale &locale);

public Q_SLOTS:
    CouchSourceList* load(Movie* item);
    CouchSourceList* load(MovieFilter *filter);
};

#endif /* LOCALMOVIEPROVIDER_H_ */
