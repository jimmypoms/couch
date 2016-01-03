#ifndef PLAYBACKHANDLERINTERFACE_H
#define PLAYBACKHANDLERINTERFACE_H

#include <qglobal.h>
#include <qobject.h>

class QMediaPlayer;
class Source;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT PlaybackHandlerInterface
{
public:
    virtual ~PlaybackHandlerInterface() = default;

    virtual QString name() = 0;
    virtual void setMediaPlayer(QMediaPlayer* p) = 0;
    virtual QMediaPlayer *mediaPlayer() = 0;

    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void pause() = 0;
    virtual void seek(qint64 position) = 0;
    virtual void load(const Source *source) = 0;

    virtual qint64 duration() const = 0;
    virtual qint64 position() const = 0;

    virtual int supports(const Source *source) = 0;
};

Q_DECLARE_INTERFACE(PlaybackHandlerInterface, "org.couch.PlaybackHandler")

#endif // PLAYBACKHANDLERINTERFACE_H
