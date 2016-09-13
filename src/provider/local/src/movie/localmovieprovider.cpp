/*
 * localmovieprovider.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: jimmypoms
 */

#include "localmovieprovider.h"

#include "couch/couchsourcelist.h"
#include "couch/movie/moviemetadata.h"
#include "couch/serializableclass.h"

#include <qbytearray.h>
#include <qdatastream.h>
#include <qfuture.h>
#include <qfuturewatcher.h>
#include <qiodevice.h>
#include <qobject.h>
#include <qstandardpaths.h>
#include <qstringlist.h>
#include <qtconcurrentrun.h>
#include <xapian/database.h>
#include <xapian/document.h>
#include <xapian/enquire.h>
#include <xapian/query.h>
#include <xapian/queryparser.h>
#include <xapian/termgenerator.h>

const QStringList LocalMovieProvider::s_filenameFilters = {
        "*.mp4",
        "*.mkv",
        "*.avi",
        "*.mpg",
        "*.mpeg"};
const std::string LocalMovieProvider::s_prefixTitle = "S";
const std::string LocalMovieProvider::s_prefixTagline = "T";
const std::string LocalMovieProvider::s_prefixYear = "Y";
const std::string LocalMovieProvider::s_prefixDirector = "D";
const std::string LocalMovieProvider::s_prefixActor = "A";
const std::string LocalMovieProvider::s_prefixGenre = "G";

LocalMovieProvider::LocalMovieProvider(QObject* parent) :
                MovieProvider(parent, "local"),
                LocalProvider(
                        QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                                + "/database/movie", "/misc/movies")
{
    Q_INIT_RESOURCE(resources);
}

QStringList LocalMovieProvider::filenameFilters() const
{
    return s_filenameFilters;
}

Xapian::Query LocalMovieProvider::buildQuery(Xapian::QueryParser &qp, const Movie* item)
{
    qp.add_prefix("title", s_prefixTitle);
    Xapian::Query query = qp.parse_query(item->name().toStdString(),
            Xapian::QueryParser::FLAG_DEFAULT | Xapian::QueryParser::FLAG_SPELLING_CORRECTION,
            s_prefixTitle);
    return query;
}

Xapian::Query LocalMovieProvider::buildQuery(Xapian::QueryParser &qp, const MovieFilter* filter)
{
    Xapian::Query query = Xapian::Query::MatchAll;
    qp.add_prefix("", s_prefixTitle);
    qp.add_prefix("", s_prefixActor);
    qp.add_prefix("", s_prefixDirector);

    if (!filter->text().isEmpty()) {
        query = qp.parse_query(filter->text().toStdString(),
                Xapian::QueryParser::FLAG_DEFAULT | Xapian::QueryParser::FLAG_SPELLING_CORRECTION
                        | Xapian::QueryParser::FLAG_PARTIAL);
    }

    if (filter->genre() != Movie::Genre::All) {
        Xapian::Query genreFilter(
                s_prefixGenre + Movie::genreToString(filter->genre()).toStdString());
        query = Xapian::Query(Xapian::Query::OP_FILTER, query, genreFilter);
    }

    return query;
}

void LocalMovieProvider::searchFinished(const Xapian::MSet& matches, const QString& id)
{
    QList<Source*> sources;

    for (Xapian::MSetIterator i = matches.begin(); i != matches.end(); ++i) {
        Source* s = new Source();
        MovieMetadata* metadata = new MovieMetadata();
        QByteArray data = QByteArray::fromStdString(i.get_document().get_data());
        QDataStream stream(data);
        stream >> *s;
        stream >> *metadata;
        s->setItemMetadata(metadata);
        sources.append(s);
    }

    Q_EMIT sourcesReady(sources, id);
}

void LocalMovieProvider::indexFile(Xapian::WritableDatabase& writer, Xapian::TermGenerator& indexer,
        Source &source)
{
    MovieMetadata metadata;
    m_metadataFetcher.fetch(metadata, source);
    if (metadata.name().isEmpty()) {
        return;
    }

    QByteArray data;
    QDataStream dataStream(&data, QIODevice::ReadWrite);
    dataStream << source;
    dataStream << metadata;

    Xapian::Document doc;
    doc.set_data(data.toStdString());
    indexer.set_document(doc);
    indexer.index_text(metadata.name().toStdString(), 1, s_prefixTitle);
    indexer.index_text(metadata.tagline().toStdString(), 1, s_prefixTagline);
    indexer.index_text(std::to_string(metadata.year()), 1, s_prefixYear);
    for (const QString &actor : metadata.actors()) {
        indexer.index_text(actor.toStdString(), 1, s_prefixActor);
    }
    for (const QString director : metadata.directors()) {
        indexer.index_text(director.toStdString(), 1, s_prefixDirector);
    }
    for (const QString genre : metadata.genres()) {
        indexer.index_text(genre.toStdString(), 1, s_prefixGenre);
    }
    m_mutex.lock();
    writer.add_document(doc);
    m_mutex.unlock();
}

CouchSourceList* LocalMovieProvider::load(Movie* movie)
{
    if (!m_isIndexing) {
        m_reader.reopen();
    }
    CouchSourceList* list = new CouchSourceList(this);
    const QString id = list->id();

    QFutureWatcher<Xapian::MSet> *watcher = new QFutureWatcher<Xapian::MSet>(list);
    connect(watcher, &QFutureWatcherBase::finished, this, [=]() {
        searchFinished(watcher->result(), id);
    });
    connect(this, &LocalMovieProvider::sourcesReady, list, &CouchSourceList::addSources);
    QFuture<Xapian::MSet> future = QtConcurrent::run(this,
            static_cast<Xapian::MSet (LocalMovieProvider::*)(
                    const Movie*)>(&LocalMovieProvider::searchDatabase), movie);
    watcher->setFuture(future);

    return list;
}

QString LocalMovieProvider::playIcon() const
{
    return "qrc:localmovieprovider/icons/play.svg";
}

CouchSourceList* LocalMovieProvider::load(MovieFilter* movieFilter)
{
    if (!m_isIndexing) {
        m_reader.reopen();
    }
    CouchSourceList* list = new CouchSourceList(this);
    const QString id = list->id();

    QFutureWatcher<Xapian::MSet> *watcher = new QFutureWatcher<Xapian::MSet>(list);
    connect(watcher, &QFutureWatcherBase::finished, this, [=]() {
        searchFinished(watcher->result(), id);
    });
    connect(this, &LocalMovieProvider::sourcesReady, list, &CouchSourceList::addSources);
    QFuture<Xapian::MSet> future = QtConcurrent::run(this,
            static_cast<Xapian::MSet (LocalMovieProvider::*)(
                    const MovieFilter*)>(&LocalMovieProvider::searchDatabase), movieFilter);
    watcher->setFuture(future);

    return list;
}
