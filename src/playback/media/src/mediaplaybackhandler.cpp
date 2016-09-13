#include "mediaplaybackhandler.h"

#include "couch/source.h"

#include <qmediaplayer.h>
#include <qmimetype.h>
#include <qstring.h>

MediaPlaybackHandler::MediaPlaybackHandler() :
        PlaybackHandler("media")
{
}

int MediaPlaybackHandler::supports(const Source *source)
{
    QMimeType type = m_mimeDb.mimeTypeForUrl(source->url());
    return QMediaPlayer::hasSupport(type.name());
}
