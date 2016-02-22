/*
 * localmusicprovider.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: jimmypoms
 */

#include "localmusicprovider.h"

#include "trackmetadatafetcher.h"

#include <qbytearray.h>
#include <qdatastream.h>
#include <qdebug.h>
#include <qdir.h>
#include <qdiriterator.h>
#include <qfuture.h>
#include <qiodevice.h>
#include <qlogging.h>
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
#include "couch/music/album.h"
#include "couch/music/artist.h"
#include "couch/music/musicfilter.h"
#include "couch/music/trackmetadata.h"
#include "couch/serializableclass.h"
#include "couch/service.h"

const QStringList LocalMusicProvider::s_fileNameFilters = {
        "*.mp3",
        "*.ogg",
        "*.aac",
        "*.wma",
        "*.mpeg"};
const std::string LocalMusicProvider::s_prefixTitle = "S";
const std::string LocalMusicProvider::s_prefixAlbum = "G";
const std::string LocalMusicProvider::s_prefixArtist = "A";
const std::string LocalMusicProvider::s_prefixYear = "Y";
const std::string LocalMusicProvider::s_prefixGenre = "G";

LocalMusicProvider::LocalMusicProvider(Service* parent) :
        MusicProvider(parent, "local"), m_isIndexing(false),
                m_database(
                        QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                                + "/database/music"), m_library("/misc/music")
{
    qRegisterMetaType<Xapian::MSet>("Xapian::MSet");
    connect(this, &LocalMusicProvider::searchFinished, this,
            &LocalMusicProvider::onSearchFinished);

    QDir().mkpath(m_database);
    Xapian::WritableDatabase writer(m_database.toStdString(), Xapian::DB_CREATE_OR_OVERWRITE);
    QtConcurrent::run(this, &LocalMusicProvider::loadDatabase, writer);

    m_reader = Xapian::Database(m_database.toStdString());
}

void LocalMusicProvider::loadDatabase(Xapian::WritableDatabase &writer)
{
    Xapian::TermGenerator indexer;
    Xapian::Stem stemmer("english");
    indexer.set_stemmer(stemmer);

    QDirIterator it(m_library, s_fileNameFilters, QDir::Files, QDirIterator::Subdirectories);
    TrackMetadataFetcher fetcher;
    qDebug() << "starting indexing of files in library path:" << m_library;
    m_isIndexing = true;
    while (it.hasNext()) {
        QString filePath = it.next();

        Source source;
        source.setUrl(QUrl::fromLocalFile(filePath));
        TrackMetadata* metadata = fetcher.fetch(&source);
        source.setItemMetadata(metadata);
        indexFile(writer, indexer, source, metadata);
    }
    writer.commit();
    m_isIndexing = false;
    qDebug() << "finished indexing files";
}

void LocalMusicProvider::indexFile(Xapian::WritableDatabase& writer,
        Xapian::TermGenerator& indexer, const Source &source, TrackMetadata* metadata)
{
    if (metadata->name().isEmpty()) {
        return;
    }

    QByteArray data;
    QDataStream dataStream(&data, QIODevice::ReadWrite);
    dataStream << source;
    dataStream << *metadata;

    Xapian::Document doc;
    doc.set_data(data.toStdString());
    indexer.set_document(doc);
    indexer.index_text(metadata->name().toStdString(), 1, s_prefixTitle);
    indexer.index_text(metadata->album().toStdString(), 1, s_prefixAlbum);
    indexer.index_text(metadata->artist().toStdString(), 1, s_prefixArtist);
    indexer.index_text(std::to_string(metadata->year()), 1, s_prefixYear);
    for (const QString genre : metadata->genres()) {
        indexer.index_text(genre.toStdString(), 1, s_prefixGenre);
    }
    writer.add_document(doc);
}

void LocalMusicProvider::searchDatabase(const MusicFilter *filter, const QString &id)
{
    Xapian::QueryParser qp;
    Xapian::Stem stemmer("english");
    Xapian::Query query = Xapian::Query::MatchAll;
    if (!filter->text().isEmpty()) {
        qp.set_stemmer(stemmer);
        qp.set_database(m_reader);
        qp.set_stemming_strategy(Xapian::QueryParser::STEM_SOME);
        qp.add_prefix("", s_prefixTitle);
        qp.add_prefix("", s_prefixAlbum);
        qp.add_prefix("", s_prefixArtist);
        Xapian::Query filterQuery = qp.parse_query(filter->text().toStdString(),
                Xapian::QueryParser::FLAG_DEFAULT
                        | Xapian::QueryParser::FLAG_SPELLING_CORRECTION
                        | Xapian::QueryParser::FLAG_PARTIAL);
        query = Xapian::Query(Xapian::Query::OP_AND, query, filterQuery);
    }
    if (filter->genre() != Album::Genre::All) {
        Xapian::Query genreFilter(
                s_prefixGenre + Album::genreToString(filter->genre()).toStdString());
        query = Xapian::Query(Xapian::Query::OP_FILTER, query, genreFilter);
    }
    Xapian::Enquire enquire(m_reader);
    enquire.set_query(query);
    qDebug() << "loading provider" << name() << ":"
            << QString::fromStdString(enquire.get_description());

    Xapian::MSet matches = enquire.get_mset(0, 10);
    Q_EMIT searchFinished(matches, id);
}

void LocalMusicProvider::searchDatabase(const Artist *artist, const QString &id)
{
    Xapian::QueryParser qp;
    Xapian::Stem stemmer("english");
    qp.set_stemmer(stemmer);
    qp.set_database(m_reader);
    qp.set_stemming_strategy(Xapian::QueryParser::STEM_SOME);
    qp.add_prefix("title", s_prefixTitle);
    qp.add_prefix("album", s_prefixAlbum);
    qp.add_prefix("artist", s_prefixArtist);
    Xapian::Query query = qp.parse_query(artist->name().toStdString(),
            Xapian::QueryParser::FLAG_DEFAULT | Xapian::QueryParser::FLAG_SPELLING_CORRECTION,
            s_prefixTitle);
    Xapian::Enquire enquire(m_reader);
    enquire.set_query(query);
    qDebug() << "loading provider" << name() << ":"
            << QString::fromStdString(enquire.get_description());

    Xapian::MSet matches = enquire.get_mset(0, 10);
    Q_EMIT searchFinished(matches, id);
}

void LocalMusicProvider::onSearchFinished(const Xapian::MSet &matches, const QString &id)
{
    QList<Source*> sources;

    for (Xapian::MSetIterator i = matches.begin(); i != matches.end(); ++i) {
        Source* s = new Source();
        ArtistMetadata* metadata = new ArtistMetadata();
        QByteArray data = QByteArray::fromStdString(i.get_document().get_data());
        QDataStream stream(data);
        stream >> *s;
        stream >> *metadata;
        s->setItemMetadata(metadata);
        sources.append(s);
    }

    Q_EMIT sourcesReady(sources, id);
}

CouchSourceList* LocalMusicProvider::load(MusicFilter* filter)
{
    if (!m_isIndexing) {
        m_reader.reopen();
    }
    CouchSourceList* list = new CouchSourceList(this);
    const QString id = list->id();

    connect(this, &LocalMusicProvider::sourcesReady, list, &CouchSourceList::addSources);
    QtConcurrent::run(this,
            static_cast<void (LocalMusicProvider::*)(const MusicFilter*,
                    const QString &)>(&LocalMusicProvider::searchDatabase), filter, id);

    return list;
}

CouchSourceList* LocalMusicProvider::load(Artist* artist)
{
    if (!m_isIndexing) {
        m_reader.reopen();
    }
    CouchSourceList* list = new CouchSourceList(this);
    const QString id = list->id();

    connect(this, &LocalMusicProvider::sourcesReady, list, &CouchSourceList::addSources);
    QtConcurrent::run(this,
            static_cast<void (LocalMusicProvider::*)(const Artist*,
                    const QString &)>(&LocalMusicProvider::searchDatabase), artist, id);

    return list;
}
