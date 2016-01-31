/*
 * localmovieprovider.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: jimmypoms
 */

#include "localmovieprovider.h"

#include "moviemetadatafetcher.h"

#include <qbytearray.h>
#include <qdatastream.h>
#include <qdebug.h>
#include <qdir.h>
#include <qdiriterator.h>
#include <qfuture.h>
#include <qiodevice.h>
#include <qlogging.h>
#include <qmetatype.h>
#include <qobject.h>
#include <qstandardpaths.h>
#include <qstringlist.h>
#include <qtconcurrentrun.h>
#include <qurl.h>
#include <xapian/document.h>
#include <xapian/enquire.h>
#include <xapian/query.h>
#include <xapian/queryparser.h>
#include <xapian/stem.h>
#include <xapian/termgenerator.h>

#include "couch/couchsourcelist.h"
#include "couch/movie/movie.h"
#include "couch/movie/moviefilter.h"
#include "couch/movie/moviemetadata.h"
#include "couch/serializableclass.h"
#include "couch/service.h"

const QStringList LocalMovieProvider::s_fileNameFilters = {
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

LocalMovieProvider::LocalMovieProvider(Service* parent) :
        MovieProvider(parent, "local"), m_isIndexing(false),
                m_database(
                        QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                                + "/database/movie"), m_library("/misc/movies"),
                m_reader(m_database.toStdString())
{
    connect(this, &LocalMovieProvider::searchFinished, this,
            &LocalMovieProvider::onSearchFinished);
    qRegisterMetaType<Xapian::MSet>("Xapian::MSet");
    QDir().mkpath(m_database);

    QtConcurrent::run(this, &LocalMovieProvider::loadDatabase);
}

void LocalMovieProvider::loadDatabase()
{
    Xapian::WritableDatabase writer(m_database.toStdString(), Xapian::DB_CREATE_OR_OVERWRITE);
    Xapian::TermGenerator indexer;
    Xapian::Stem stemmer("english");
    indexer.set_stemmer(stemmer);

    QDirIterator it(m_library, s_fileNameFilters, QDir::Files, QDirIterator::Subdirectories);
    MovieMetadataFetcher fetcher;
    qDebug() << "starting indexing of files in library path:" << m_library;
    m_isIndexing = true;
    while (it.hasNext()) {
        QString filePath = it.next();

        Source source;
        source.setUrl(QUrl::fromLocalFile(filePath));
        MovieMetadata* metadata = fetcher.fetch(&source);
        source.setItemMetadata(metadata);
        indexFile(writer, indexer, source, metadata);
    }
    writer.commit();
    m_isIndexing = false;
    qDebug() << "finished indexing files";
}

void LocalMovieProvider::indexFile(Xapian::WritableDatabase& writer,
        Xapian::TermGenerator& indexer, const Source &source, MovieMetadata* metadata)
{
    if (metadata->title().isEmpty()) {
        return;
    }

    QByteArray data;
    QDataStream dataStream(&data, QIODevice::ReadWrite);
    dataStream << source;
    dataStream << *metadata;

    Xapian::Document doc;
    doc.set_data(data.toStdString());
    indexer.set_document(doc);
    indexer.index_text(metadata->title().toStdString(), 1, s_prefixTitle);
    indexer.index_text(metadata->tagline().toStdString(), 1, s_prefixTagline);
    indexer.index_text(std::to_string(metadata->year()), 1, s_prefixYear);
    for (const QString &actor : metadata->actors()) {
        indexer.index_text(actor.toStdString(), 1, s_prefixActor);
    }
    for (const QString director : metadata->directors()) {
        indexer.index_text(director.toStdString(), 1, s_prefixDirector);
    }
    for (const QString genre : metadata->genres()) {
        indexer.index_text(genre.toStdString(), 1, s_prefixGenre);
    }
    writer.add_document(doc);
}

void LocalMovieProvider::searchDatabase(const MovieFilter *filter, const QString &id)
{
    Xapian::QueryParser qp;
    Xapian::Stem stemmer("english");
    Xapian::Query query = Xapian::Query::MatchAll;
    if (!filter->text().isEmpty()) {
        qp.set_stemmer(stemmer);
        qp.set_database(m_reader);
        qp.set_stemming_strategy(Xapian::QueryParser::STEM_SOME);
        qp.add_prefix("", s_prefixTitle);
        qp.add_prefix("", s_prefixActor);
        qp.add_prefix("", s_prefixDirector);
        Xapian::Query filterQuery = qp.parse_query(filter->text().toStdString(),
                Xapian::QueryParser::FLAG_DEFAULT
                        | Xapian::QueryParser::FLAG_SPELLING_CORRECTION
                        | Xapian::QueryParser::FLAG_PARTIAL);
        query = Xapian::Query(Xapian::Query::OP_AND, query, filterQuery);
    }
    if (filter->genre() != Movie::Genre::All) {
        Xapian::Query genreFilter(
                s_prefixGenre + Movie::genreToString(filter->genre()).toStdString());
        query = Xapian::Query(Xapian::Query::OP_FILTER, query, genreFilter);
    }
    Xapian::Enquire enquire(m_reader);
    enquire.set_query(query);
    qDebug() << "loading provider" << name() << ":"
            << QString::fromStdString(enquire.get_description());

    Xapian::MSet matches = enquire.get_mset(0, 10);
    Q_EMIT searchFinished(matches, id);
}

void LocalMovieProvider::searchDatabase(const Movie *movie, const QString &id)
{
    Xapian::QueryParser qp;
    Xapian::Stem stemmer("english");
    qp.set_stemmer(stemmer);
    qp.set_database(m_reader);
    qp.set_stemming_strategy(Xapian::QueryParser::STEM_SOME);
    qp.add_prefix("title", s_prefixTitle);
    qp.add_prefix("actor", s_prefixActor);
    qp.add_prefix("director", s_prefixDirector);
    Xapian::Query query = qp.parse_query(movie->title().toStdString(),
            Xapian::QueryParser::FLAG_DEFAULT | Xapian::QueryParser::FLAG_SPELLING_CORRECTION,
            s_prefixTitle);
    Xapian::Enquire enquire(m_reader);
    enquire.set_query(query);
    qDebug() << "loading provider" << name() << ":"
            << QString::fromStdString(enquire.get_description());

    Xapian::MSet matches = enquire.get_mset(0, 10);
    Q_EMIT searchFinished(matches, id);
}

void LocalMovieProvider::onSearchFinished(const Xapian::MSet &matches, const QString &id)
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

CouchSourceList* LocalMovieProvider::load(MovieFilter* movieFilter)
{
    CouchSourceList* list = new CouchSourceList(this);
    const QString id = list->id();

    connect(this, &LocalMovieProvider::sourcesReady, list, &CouchSourceList::addSources);
    QtConcurrent::run(this,
            static_cast<void (LocalMovieProvider::*)(const MovieFilter*,
                    const QString &)>(&LocalMovieProvider::searchDatabase), movieFilter, id);

    if (!m_isIndexing) {
        m_reader.reopen();
    }
    return list;
}

CouchSourceList* LocalMovieProvider::load(Movie* movie)
{
    CouchSourceList* list = new CouchSourceList(this);
    const QString id = list->id();

    connect(this, &LocalMovieProvider::sourcesReady, list, &CouchSourceList::addSources);
    QtConcurrent::run(this,
            static_cast<void (LocalMovieProvider::*)(const Movie*,
                    const QString &)>(&LocalMovieProvider::searchDatabase), movie, id);

    if (!m_isIndexing) {
        m_reader.reopen();
    }
    return list;
}
