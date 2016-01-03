/*
 * movieinfofetcher.h
 *
 *  Created on: 4 Nov 2015
 *      Author: jimmypoms
 */

#ifndef MOVIEMETADATAFETCHER_H_
#define MOVIEMETADATAFETCHER_H_

#include <qstring.h>

class MovieMetadata;
class QUrl;
class QXmlStreamReader;

class MovieMetadataFetcher
{
    bool fetchNfoMetadata(MovieMetadata* metadata, const QString &path);
    void readMovieTag(QXmlStreamReader &xml, MovieMetadata *metadata);
    void readActorTag(QXmlStreamReader &xml, MovieMetadata *metadata);
    void readFanartTag(QXmlStreamReader &xml, MovieMetadata *metadata);
    QUrl readTrailerTag(QXmlStreamReader &xml);
    QString readStringTag(QXmlStreamReader &xml);
    QUrl readUrlTag(QXmlStreamReader &xml);
    int readIntTag(QXmlStreamReader &xml);
    double readDoubleTag(QXmlStreamReader &xml);

    bool fetchFileMetadata(MovieMetadata* metadata, const QString &path);

public:
    MovieMetadataFetcher() = default;
    virtual ~MovieMetadataFetcher() = default;

    MovieMetadata* fetch(const QString &filePath);
};

#endif /* MOVIEMETADATAFETCHER_H_ */
