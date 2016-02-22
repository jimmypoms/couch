/*
 * artistmetadatafetcher.h
 *
 *  Created on: 21 Feb 2016
 *      Author: jimmypoms
 */

#ifndef TRACKMETADATAFETCHER_H_
#define TRACKMETADATAFETCHER_H_

#include <MediaInfoDLL/MediaInfoDLL.h>
#include <qfileinfo.h>

class Source;
class TrackMetadata;

class TrackMetadataFetcher
{
    MediaInfoDLL::MediaInfo m_mediaInfoHandle;

    bool fetchFileMetadata(TrackMetadata* metadata, const QFileInfo &fileInfo);

public:
    TrackMetadataFetcher();
    virtual ~TrackMetadataFetcher() = default;

    TrackMetadata* fetch(Source *source);
};

#endif /* TRACKMETADATAFETCHER_H_ */
