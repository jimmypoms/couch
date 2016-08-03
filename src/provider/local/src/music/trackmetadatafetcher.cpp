/*
 * artistmetadatafetcher.cpp
 *
 *  Created on: 21 Feb 2016
 *      Author: jimmypoms
 */

#include "trackmetadatafetcher.h"

#include <qbytearray.h>
#include <qchar.h>
#include <qcryptographichash.h>
#include <qfile.h>
#include <qiodevice.h>
#include <qstandardpaths.h>
#include <qstring.h>
#include <qstringlist.h>
#include <string>

#include "couch/music/trackmetadata.h"
#include "couch/source.h"

using namespace MediaInfoDLL;

TrackMetadataFetcher::TrackMetadataFetcher() :
                m_coverCacheDir(
                        QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                                + "/cache/music/cover")
{
    m_mediaInfoHandle.Option("Internet", "No");
    m_coverCacheDir.mkpath(m_coverCacheDir.absolutePath());
}

void TrackMetadataFetcher::fetch(TrackMetadata &metadata, Source &source)
{
    QFileInfo fileInfo(source.url().toLocalFile());
    if (!fileInfo.exists()) {
        return;
    }

    m_mediaInfoHandle.Open(source.url().toLocalFile().toStdString());
    std::string bitRate(m_mediaInfoHandle.Get(Stream_Audio, 0, "OverallBitRate/String"));

    source.setSizeBytes(fileInfo.size());
    source.setQuality(QString::fromStdString(bitRate));
    fetchFileMetadata(metadata, fileInfo);

    m_mediaInfoHandle.Close();
}

bool TrackMetadataFetcher::fetchFileMetadata(TrackMetadata &metadata,
        const QFileInfo &fileInfo)
{
    metadata.setArtist(
            QString::fromStdString(m_mediaInfoHandle.Get(Stream_General, 0, "Performer")));
    metadata.setAlbum(
            QString::fromStdString(m_mediaInfoHandle.Get(Stream_General, 0, "Album")));
    metadata.setTrack(
            QString::fromStdString(m_mediaInfoHandle.Get(Stream_General, 0, "Track")));
    metadata.setDescription(
            QString::fromStdString(m_mediaInfoHandle.Get(Stream_General, 0, "Description")));
    QStringList genres = QString::fromStdString(
            m_mediaInfoHandle.Get(Stream_General, 0, "Genre")).split(';');
    metadata.setGenres(genres);
    metadata.setYear(
            QString::fromStdString(m_mediaInfoHandle.Get(Stream_General, 0, "Recorded_Date")).toInt());

    std::string albumArtData(m_mediaInfoHandle.Get(Stream_General, 0, "Cover_Data"));
    QString stringKey(metadata.artist() + metadata.album());
    QString albumArtFilename(
            QCryptographicHash::hash(stringKey.toLocal8Bit(), QCryptographicHash::Md5).toHex());
    QFile albumArtFile(m_coverCacheDir.filePath(albumArtFilename));
    if (!albumArtData.empty()) {
        if (!albumArtFile.exists() && albumArtFile.open(QIODevice::ReadWrite)) {
            albumArtFile.write(QByteArray::fromBase64(QByteArray::fromStdString(albumArtData)));
            albumArtFile.close();
        }
        metadata.setAlbumCover(QUrl::fromLocalFile(m_coverCacheDir.filePath(albumArtFilename)));
    }

    return true;
}
