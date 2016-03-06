/*
 * localmusicprovider.h
 *
 *  Created on: 21 Feb 2016
 *      Author: jimmypoms
 */

#ifndef LOCALMUSICPROVIDER_H_
#define LOCALMUSICPROVIDER_H_

#include "trackmetadatafetcher.h"

#include <qlist.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <string>

#include "../common/localprovider.h"
#include "couch/music/artist.h"
#include "couch/music/musicfilter.h"
#include "couch/music/musicprovider.h"
#include "couch/source.h"

class LocalMusicProvider : public MusicProvider, public LocalProvider<Artist, MusicFilter>
{
Q_OBJECT

Q_PLUGIN_METADATA(IID "org.couch.provider.local.music")
Q_INTERFACES(MusicProviderInterface)

Q_SIGNALS:
    void sourcesReady(const QList<Source*> &sources, const QString &id);

private:
    static const QStringList s_filenameFilters;
    static const std::string s_prefixTitle;
    static const std::string s_prefixAlbum;
    static const std::string s_prefixArtist;
    static const std::string s_prefixYear;
    static const std::string s_prefixGenre;

    TrackMetadataFetcher m_metadataFetcher;

    void searchFinished(const Xapian::MSet &matches, const QString &id);

    QStringList filenameFilters() const;
    Xapian::Query buildQuery(Xapian::QueryParser &qp, const Artist *item);
    Xapian::Query buildQuery(Xapian::QueryParser &qp, const MusicFilter *filter);
    void indexFile(Xapian::WritableDatabase &writer, Xapian::TermGenerator &indexer,
            Source &source);

public:
    explicit LocalMusicProvider(QObject* parent = 0);
    virtual ~LocalMusicProvider() = default;

public Q_SLOTS:
    CouchSourceList* load(Artist* item);
    CouchSourceList* load(MusicFilter *filter);
};

#endif /* LOCALMUSICPROVIDER_H_ */
