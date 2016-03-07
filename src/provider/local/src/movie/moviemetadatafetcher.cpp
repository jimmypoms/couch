/*
 * movieinfofetcher.cpp
 *
 *  Created on: 4 Nov 2015
 *      Author: jimmypoms
 */

#include "moviemetadatafetcher.h"

#include <qfile.h>
#include <qglobal.h>
#include <qiodevice.h>
#include <qstring.h>
#include <qurl.h>
#include <qxmlstream.h>

#include "couch/movie/moviemetadata.h"
#include "couch/source.h"

using namespace MediaInfoDLL;

MovieMetadataFetcher::MovieMetadataFetcher()
{
    m_mediaInfoHandle.Option("Internet", "No");
}

bool MovieMetadataFetcher::fetchNfoMetadata(MovieMetadata* metadata, const QFileInfo &fileInfo)
{
    QFile nfoFile(fileInfo.absolutePath() + "/" + fileInfo.completeBaseName() + ".nfo");
    if (!nfoFile.exists()) {
        return false;
    }
    if (!nfoFile.open(QIODevice::ReadOnly)) {
        return false;
    }
    QXmlStreamReader xml(&nfoFile);
    while (!xml.atEnd() && xml.readNextStartElement()) {
        if (xml.name() == "movie") {
            readMovieTag(xml, metadata);
        } else {
            xml.skipCurrentElement();
        }
    }
    return true;
}

void MovieMetadataFetcher::readMovieTag(QXmlStreamReader &xml, MovieMetadata* metadata)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "movie");
    while (xml.readNextStartElement()) {
        if (xml.name() == "actor") {
            readActorTag(xml, metadata);
        } else if (xml.name() == "fanart") {
            readFanartTag(xml, metadata);
        } else if (xml.name() == "title") {
            metadata->setName(readStringTag(xml));
        } else if (xml.name() == "tagline") {
            metadata->setTagline(readStringTag(xml));
        } else if (xml.name() == "year") {
            metadata->setYear(readIntTag(xml));
        } else if (xml.name() == "popularity") {
            metadata->setPopularity(readIntTag(xml) / 100);
        } else if (xml.name() == "rating") {
            metadata->setRating(readDoubleTag(xml) / 10.0);
        } else if (xml.name() == "runtime") {
            metadata->setRuntime(readIntTag(xml));
        } else if (xml.name() == "thumb") {
            if (metadata->image().isEmpty()) {
                metadata->setImage(QUrl(xml.attributes().value("preview").toString()));
            } else {
                xml.skipCurrentElement();
            }
            xml.readElementText(QXmlStreamReader::SkipChildElements);
        } else if (xml.name() == "plot") {
            metadata->setDescription(readStringTag(xml));
        } else if (xml.name() == "genre") {
            metadata->addGenre(readStringTag(xml));
        } else if (xml.name() == "country") {
            metadata->setCountry(readStringTag(xml));
        } else if (xml.name() == "credits") {
            metadata->addCredit(readStringTag(xml));
        } else if (xml.name() == "director") {
            metadata->addDirector(readStringTag(xml));
        } else if (xml.name() == "studio") {
            metadata->setStudio(readStringTag(xml));
        } else if (xml.name() == "trailer") {
            metadata->setTrailer(readTrailerTag(xml));
        } else {
            xml.skipCurrentElement();
        }
    }
}

void MovieMetadataFetcher::readActorTag(QXmlStreamReader &xml, MovieMetadata* metadata)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "actor");

    while (xml.readNextStartElement()) {
        if (xml.name() == "name") {
            metadata->addActor(readStringTag(xml));
        } else {
            xml.skipCurrentElement();
        }
    }
}

void MovieMetadataFetcher::readFanartTag(QXmlStreamReader &xml, MovieMetadata* metadata)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "fanart");

    while (xml.readNextStartElement()) {
        if (metadata->poster().isEmpty() && xml.name() == "thumb") {
            metadata->setPoster(readUrlTag(xml));
        } else {
            xml.skipCurrentElement();
        }
    }
}

QUrl MovieMetadataFetcher::readTrailerTag(QXmlStreamReader &xml)
{
    QString trailer = xml.readElementText(QXmlStreamReader::SkipChildElements);
    trailer.replace("plugin://plugin.video.youtube/?action=play_video&videoid=",
            "https://www.youtube.com/watch?v=");
    return QUrl(trailer);
}

QString MovieMetadataFetcher::readStringTag(QXmlStreamReader &xml)
{
    return xml.readElementText(QXmlStreamReader::SkipChildElements);
}

int MovieMetadataFetcher::readIntTag(QXmlStreamReader &xml)
{
    return xml.readElementText(QXmlStreamReader::SkipChildElements).toInt();
}

double MovieMetadataFetcher::readDoubleTag(QXmlStreamReader &xml)
{
    return xml.readElementText(QXmlStreamReader::SkipChildElements).toDouble();
}

QUrl MovieMetadataFetcher::readUrlTag(QXmlStreamReader& xml)
{
    return QUrl(xml.readElementText(QXmlStreamReader::SkipChildElements));
}

bool MovieMetadataFetcher::fetchFileMetadata(MovieMetadata* metadata,
        const QFileInfo &fileInfo)
{
    return false;
}

MovieMetadata* MovieMetadataFetcher::fetch(Source *source)
{
    MovieMetadata* metadata = new MovieMetadata();
    QFileInfo fileInfo(source->url().toLocalFile());
    if (!fileInfo.exists()) {
        return nullptr;
    }
    m_mediaInfoHandle.Open(source->url().toLocalFile().toStdString());

    std::string width(m_mediaInfoHandle.Get(Stream_Video, 0, "Width"));
    std::string height(m_mediaInfoHandle.Get(Stream_Video, 0, "Height"));

    source->setSizeBytes(fileInfo.size());
    source->setQuality(QString::fromStdString(width + " x " + height));
    if (fetchNfoMetadata(metadata, fileInfo)) {
        return metadata;
    }
    if (fetchFileMetadata(metadata, fileInfo)) {
        return metadata;
    }
    return metadata;
}
