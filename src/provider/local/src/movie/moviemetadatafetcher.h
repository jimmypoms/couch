/*
 * movieinfofetcher.h
 *
 *  Created on: 4 Nov 2015
 *      Author: jimmypoms
 */

#ifndef MOVIEMETADATAFETCHER_H_
#define MOVIEMETADATAFETCHER_H_

#include <MediaInfoDLL/MediaInfoDLL.h>
#include <qfileinfo.h>
#include <string>

class Source;

class QUrl;
class MovieMetadata;
class QXmlStreamReader;

class MovieMetadataFetcher
{
    MediaInfoDLL::MediaInfo m_mediaInfoHandle;

    bool fetchNfoMetadata(MovieMetadata &metadata, const QFileInfo &fileInfo);
    void readMovieTag(QXmlStreamReader &xml, MovieMetadata &metadata);
    void readActorTag(QXmlStreamReader &xml, MovieMetadata &metadata);
    void readFanartTag(QXmlStreamReader &xml, MovieMetadata &metadata);
    QUrl readTrailerTag(QXmlStreamReader &xml);
    QString readStringTag(QXmlStreamReader &xml);
    QUrl readUrlTag(QXmlStreamReader &xml);
    int readIntTag(QXmlStreamReader &xml);
    double readDoubleTag(QXmlStreamReader &xml);

    bool fetchFileMetadata(MovieMetadata &metadata, const QFileInfo &fileInfo);

public:
    MovieMetadataFetcher();
    virtual ~MovieMetadataFetcher() = default;

    void fetch(MovieMetadata &metadata, Source &source);
};

#endif /* MOVIEMETADATAFETCHER_H_ */
