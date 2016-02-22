/*
 * localmusicprovider.h
 *
 *  Created on: 21 Feb 2016
 *      Author: jimmypoms
 */

#ifndef LOCALMUSICPROVIDER_H_
#define LOCALMUSICPROVIDER_H_

#include <qlist.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <xapian/database.h>
#include <atomic>
#include <string>

#include "couch/music/musicprovider.h"
#include "couch/source.h"

class TrackMetadata;

namespace Xapian
{
class MSet;
class TermGenerator;
} /* namespace Xapian */

class LocalMusicProvider : public MusicProvider
{
Q_OBJECT

Q_PLUGIN_METADATA(IID "org.couch.provider.local.music")
Q_INTERFACES(MusicProviderInterface)

Q_SIGNALS:
    void sourcesReady(const QList<Source*> &sources, const QString &id);
    void searchFinished(const Xapian::MSet &matches, const QString &id);

private:
    static const QStringList s_fileNameFilters;
    static const std::string s_prefixTitle;
    static const std::string s_prefixAlbum;
    static const std::string s_prefixArtist;
    static const std::string s_prefixYear;
    static const std::string s_prefixGenre;

    std::atomic_bool m_isIndexing;
    QString m_database;
    QString m_library;
    Xapian::Database m_reader;

    void searchDatabase(const MusicFilter *filter, const QString &id);
    void searchDatabase(const Artist *artist, const QString &id);
    void loadDatabase(Xapian::WritableDatabase &writer);
    void indexFile(Xapian::WritableDatabase &writer, Xapian::TermGenerator &indexer,
            const Source &source, TrackMetadata* info);

private Q_SLOTS:
    void onSearchFinished(const Xapian::MSet &result, const QString &id);

public:
    explicit LocalMusicProvider(Service* parent = 0);
    virtual ~LocalMusicProvider() = default;

public Q_SLOTS:
    CouchSourceList* load(MusicFilter *filter);
    CouchSourceList* load(Artist* item);
};

#endif /* LOCALMUSICPROVIDER_H_ */
