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

    static bool fetchNfoMetadata(MovieMetadata &metadata, const QFileInfo &fileInfo);
    static void readMovieTag(QXmlStreamReader &xml, MovieMetadata &metadata);
    static void readActorTag(QXmlStreamReader &xml, MovieMetadata &metadata);
    static void readFanartTag(QXmlStreamReader &xml, MovieMetadata &metadata);
    static QUrl readTrailerTag(QXmlStreamReader &xml);
    static QString readStringTag(QXmlStreamReader &xml);
    static QUrl readUrlTag(QXmlStreamReader &xml);
    static int readIntTag(QXmlStreamReader &xml);
    static double readDoubleTag(QXmlStreamReader &xml);

    static bool fetchFileMetadata(MovieMetadata &metadata, const QFileInfo &fileInfo);

public:
    MovieMetadataFetcher();
    virtual ~MovieMetadataFetcher() = default;

    void fetch(MovieMetadata &metadata, Source &source);
};

#endif /* MOVIEMETADATAFETCHER_H_ */
