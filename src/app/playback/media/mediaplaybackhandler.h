#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include "couch/playbackhandler.h"

class MediaPlaybackHandler : public PlaybackHandler
{
public:
    MediaPlaybackHandler();
    int supports(const Source *source);
};

#endif // MEDIACONTROL_H
