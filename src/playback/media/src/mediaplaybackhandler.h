#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include "couch/playbackhandler.h"

#include <qobjectdefs.h>

class MediaPlaybackHandler : public PlaybackHandler
{
Q_OBJECT

Q_PLUGIN_METADATA(IID "org.couch.playback.media")
Q_INTERFACES(PlaybackHandlerInterface)

public:
    MediaPlaybackHandler();
    virtual ~MediaPlaybackHandler() = default;

    int supports(const Source *source);
};

#endif // MEDIACONTROL_H
