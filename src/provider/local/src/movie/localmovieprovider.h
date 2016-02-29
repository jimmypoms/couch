/*
 * localmovieprovider.h
 *
 *  Created on: 4 Nov 2015
 *      Author: jimmypoms
 */

#ifndef LOCALMOVIEPROVIDER_H_
#define LOCALMOVIEPROVIDER_H_

#include <qlist.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <xapian/database.h>
#include <atomic>
#include <string>

#include "couch/movie/movieprovider.h"
#include "couch/source.h"

class Movie;
class MovieFilter;
class MovieMetadata;

namespace Xapian
{
class MSet;
class TermGenerator;
class WritableDatabase;
} /* namespace Xapian */

class LocalMovieProvider : public MovieProvider
{
Q_OBJECT

Q_PLUGIN_METADATA(IID "org.couch.provider.local.movie")
Q_INTERFACES(MovieProviderInterface)

Q_SIGNALS:
    void sourcesReady(const QList<Source*> &sources, const QString &id);
    void searchFinished(const Xapian::MSet &matches, const QString &id);

private:
    static const QStringList s_fileNameFilters;
    static const std::string s_prefixTitle;
    static const std::string s_prefixTagline;
    static const std::string s_prefixYear;
    static const std::string s_prefixDirector;
    static const std::string s_prefixActor;
    static const std::string s_prefixGenre;

    std::atomic_bool m_isIndexing;
    QString m_database;
    QString m_library;
    Xapian::Database m_reader;

    void searchDatabase(const MovieFilter *filter, const QString &id);
    void searchDatabase(const Movie *movie, const QString &id);
    void loadDatabase(Xapian::WritableDatabase &writer);
    void indexFile(Xapian::WritableDatabase &writer, Xapian::TermGenerator &indexer,
            const Source &source, MovieMetadata* info);

private Q_SLOTS:
    void onSearchFinished(const Xapian::MSet &result, const QString &id);

public:
    explicit LocalMovieProvider(QObject* parent = 0);
    virtual ~LocalMovieProvider() = default;

public Q_SLOTS:
    CouchSourceList* load(MovieFilter *filter);
    CouchSourceList* load(Movie* item);
};

#endif /* LOCALMOVIEPROVIDER_H_ */
