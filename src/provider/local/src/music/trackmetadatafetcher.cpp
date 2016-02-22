/*
 * artistmetadatafetcher.cpp
 *
 *  Created on: 21 Feb 2016
 *      Author: jimmypoms
 */

#include "trackmetadatafetcher.h"

#include <qstring.h>
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

    std::string bitRate = m_mediaInfoHandle.Get(Stream_Audio, 0, "BitRate");
    std::string bitRateMode = m_mediaInfoHandle.Get(Stream_Audio, 0, "BitRate_Mode");

    QFileInfo fileInfo(source->url().toLocalFile());
    source->setSizeBytes(fileInfo.size());
    source->setQuality(QString::fromStdString(bitRate + " x " + bitRateMode));
    if (fetchFileMetadata(metadata, fileInfo)) {
        return metadata;
    }
    return metadata;
}

bool TrackMetadataFetcher::fetchFileMetadata(TrackMetadata* metadata,
        const QFileInfo &fileInfo)
{
    return false;
}
