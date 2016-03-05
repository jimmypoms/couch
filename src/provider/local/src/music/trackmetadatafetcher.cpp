/*
 * artistmetadatafetcher.cpp
 *
 *  Created on: 21 Feb 2016
 *      Author: jimmypoms
 */

#include "trackmetadatafetcher.h"

#include <qchar.h>
#include <qstring.h>
#include <qstringlist.h>
#include <string>

#include "couch/music/trackmetadata.h"
#include "couch/source.h"

using namespace MediaInfoDLL;

TrackMetadataFetcher::TrackMetadataFetcher()
{
    m_mediaInfoHandle.Option("Internet", "No");
}

TrackMetadata* TrackMetadataFetcher::fetch(Source *source)
{
    TrackMetadata* metadata = new TrackMetadata();
    m_mediaInfoHandle.Open(source->url().toLocalFile().toStdString());

    std::string bitRate = m_mediaInfoHandle.Get(Stream_Audio, 0, "OverallBitRate/String");

    QFileInfo fileInfo(source->url().toLocalFile());
    source->setSizeBytes(fileInfo.size());
    source->setQuality(QString::fromStdString(bitRate));
    if (fetchFileMetadata(metadata, fileInfo)) {
        return metadata;
    }
    return metadata;
}

bool TrackMetadataFetcher::fetchFileMetadata(TrackMetadata* metadata,
        const QFileInfo &fileInfo)
{
    metadata->setArtist(
            QString::fromStdString(m_mediaInfoHandle.Get(Stream_General, 0, "Performer")));
    metadata->setAlbum(
            QString::fromStdString(m_mediaInfoHandle.Get(Stream_General, 0, "Album")));
    metadata->setTrack(
            QString::fromStdString(m_mediaInfoHandle.Get(Stream_General, 0, "Track")));
    metadata->setDescription(
            QString::fromStdString(m_mediaInfoHandle.Get(Stream_General, 0, "Description")));
    QStringList genres = QString::fromStdString(
            m_mediaInfoHandle.Get(Stream_General, 0, "Genre")).split(';');
    metadata->setGenres(genres);
    metadata->setYear(
            QString::fromStdString(m_mediaInfoHandle.Get(Stream_General, 0, "Recorded_Date")).toInt());
    return true;
}
