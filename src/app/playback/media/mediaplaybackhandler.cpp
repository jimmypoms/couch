#include "mediaplaybackhandler.h"

#include <qmediaplayer.h>
#include <qmimetype.h>
#include <qstring.h>

#include "couch/source.h"

MediaPlaybackHandler::MediaPlaybackHandler() :
        PlaybackHandler("media")
{
}

int MediaPlaybackHandler::supports(const Source *source)
{
    QMimeType type = m_mimeDb.mimeTypeForUrl(source->url());
    return QMediaPlayer::hasSupport(type.name());
}
