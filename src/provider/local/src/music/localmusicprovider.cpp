/*
 * localmusicprovider.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: jimmypoms
 */

#include "localmusicprovider.h"

#include "couch/couchsourcelist.h"
#include "couch/filter.h"
#include "couch/music/album.h"
#include "couch/music/trackmetadata.h"
#include "couch/serializableclass.h"
#include "couch/settings/foldersetting.h"
#include "couch/settings/settinglist.h"

#include <qbytearray.h>
#include <qdatastream.h>
#include <qdatetime.h>
#include <qfuture.h>
#include <qfuturewatcher.h>
#include <qglobal.h>
#include <qiodevice.h>
#include <qobject.h>
#include <qstandardpaths.h>
#include <qstringlist.h>
#include <qtconcurrentrun.h>
#include <qtranslator.h>
#include <qvariant.h>
#include <xapian/document.h>
#include <xapian.h>

const QStringList LocalMusicProvider::s_filenameFilters = {
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

LocalMusicProvider::LocalMusicProvider(QObject* parent) :
                MusicProvider(parent, "local"),
                LocalProvider(
                        QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                                + "/database/music")
{
    Q_INIT_RESOURCE(resources);
}

QStringList LocalMusicProvider::filenameFilters() const
{
    return s_filenameFilters;
}

Xapian::Query LocalMusicProvider::buildQuery(Xapian::QueryParser &qp, const Artist* item)
{
    qp.add_prefix("artist", s_prefixArtist);
    Xapian::Query query = qp.parse_query(item->name().toStdString(),
            Xapian::QueryParser::FLAG_DEFAULT | Xapian::QueryParser::FLAG_SPELLING_CORRECTION,
            s_prefixTitle);
    return query;
}

Xapian::Query LocalMusicProvider::buildQuery(Xapian::QueryParser &qp, const MusicFilter* filter)
{
    Xapian::Query query = Xapian::Query::MatchAll;

    qp.add_prefix("", s_prefixTitle);
    qp.add_prefix("", s_prefixAlbum);
    qp.add_prefix("", s_prefixArtist);

    if (!filter->text().isEmpty()) {
        query = qp.parse_query(filter->text().toStdString(),
                Xapian::QueryParser::FLAG_DEFAULT | Xapian::QueryParser::FLAG_SPELLING_CORRECTION
                        | Xapian::QueryParser::FLAG_PARTIAL);
    }

    if (filter->genre() != Album::Genre::All) {
        Xapian::Query genreFilter(
                s_prefixGenre + Album::genreToString(filter->genre()).toStdString());
        query = Xapian::Query(Xapian::Query::OP_FILTER, query, genreFilter);
    }

    return query;
}

void LocalMusicProvider::searchFinished(const Xapian::MSet &matches, const QString &id)
{
    QList<Source*> sources;

    for (Xapian::MSetIterator i = matches.begin(); i != matches.end(); ++i) {
        Source* s = new Source();
        TrackMetadata* metadata = new TrackMetadata();
        QByteArray data = QByteArray::fromStdString(i.get_document().get_data());
        QDataStream stream(data);
        stream >> *s;
        stream >> *metadata;
        s->setItemMetadata(metadata);
        sources.append(s);
    }

    Q_EMIT sourcesReady(sources, id);
}

void LocalMusicProvider::indexFile(Xapian::WritableDatabase& writer, Xapian::TermGenerator& indexer,
        Source &source)
{
    TrackMetadata metadata;
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
    doc.add_value(Filter::Newest, Xapian::sortable_serialise(metadata.addedAt().toTime_t()));
    doc.add_value(Filter::Popular, Xapian::sortable_serialise(metadata.popularity()));
    indexer.set_document(doc);
    indexer.index_text(metadata.name().toStdString(), 1, s_prefixTitle);
    indexer.index_text(metadata.album().toStdString(), 1, s_prefixAlbum);
    indexer.index_text(metadata.artist().toStdString(), 1, s_prefixArtist);
    indexer.index_text(std::to_string(metadata.year()), 1, s_prefixYear);
    for (const QString genre : metadata.genres()) {
        indexer.index_text(genre.toStdString(), 1, s_prefixGenre);
    }
    m_mutex.lock();
    writer.add_document(doc);
    m_mutex.unlock();
}

QString LocalMusicProvider::playIcon() const
{
    return "qrc:localmusicprovider/icons/play.svg";
}

SettingList* LocalMusicProvider::buildSettings(const SettingList* parent)
{
    SettingList* settings = new SettingList(this, parent, name());

    FolderSetting *folder = new FolderSetting(this, "library", "",
            //% "Library path"
            qtTrId("provider.music.local.setting.folder.title"),
            //% "Choose the local file system path where to search for audio files"
            qtTrId("provider.music.local.setting.folder.description"));
    connect(folder, &FolderSetting::valueChanged, this, [=]() {
        setLibraryPath(folder->value().toString());
    });
    settings->appendSetting(folder);

    return settings;
}

QTranslator* LocalMusicProvider::pluginTranslator(const QLocale& locale)
{
    QTranslator *translator = new QTranslator(this);

    translator->load(locale, "music", "_", ":/localmusicprovider/translations", ".qm");

    return translator;
}

CouchSourceList* LocalMusicProvider::load(MusicFilter* filter)
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
    connect(this, &LocalMusicProvider::sourcesReady, list, &CouchSourceList::addSources);
    QFuture<Xapian::MSet> future = QtConcurrent::run(this,
            static_cast<Xapian::MSet (LocalMusicProvider::*)(
                    const MusicFilter*)>(&LocalMusicProvider::searchDatabase), filter);
    watcher->setFuture(future);

    return list;
}

CouchSourceList* LocalMusicProvider::load(Artist* artist)
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
    connect(this, &LocalMusicProvider::sourcesReady, list, &CouchSourceList::addSources);
    QFuture<Xapian::MSet> future = QtConcurrent::run(this,
            static_cast<Xapian::MSet (LocalMusicProvider::*)(
                    const Artist*)>(&LocalMusicProvider::searchDatabase), artist);
    watcher->setFuture(future);

    return list;
}
