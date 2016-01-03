#ifndef PLAYBACKHANDLER_H
#define PLAYBACKHANDLER_H

#include <qglobal.h>
#include <qmediaplayer.h>
#include <qmimedatabase.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <qurl.h>

#include "../model/source.h"

#include "playbackhandlerinterface.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT PlaybackHandler : public QObject, public PlaybackHandlerInterface
{
Q_OBJECT

Q_INTERFACES(PlaybackHandlerInterface)
Q_SIGNALS:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void bufferStatusChanged(int bufferStatus);
    void loadingStatusChanged(int loadingStatus);
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void stateChanged(QMediaPlayer::State state);
    void error(QMediaPlayer::Error error);

private:
    QString m_name;

protected:
    QMimeDatabase m_mimeDb;
    QMediaPlayer *m_mediaPlayer;
    const Source *m_source;

public:
    explicit PlaybackHandler(QString name) :
            m_name(name), m_mediaPlayer(nullptr), m_source(nullptr)
    {
    }
    virtual ~PlaybackHandler() = default;

    QString name()
    {
        return m_name;
    }

    virtual void setMediaPlayer(QMediaPlayer* p)
    {
        m_mediaPlayer = p;
    }

    virtual QMediaPlayer *mediaPlayer()
    {
        return m_mediaPlayer;
    }

    virtual void play()
    {
        connect(m_mediaPlayer,
                static_cast<void (QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error), this, &PlaybackHandler::error);

        m_mediaPlayer->setMedia(m_source->url());

        connect(m_mediaPlayer, &QMediaPlayer::durationChanged,
            this, &PlaybackHandler::durationChanged);
        connect(m_mediaPlayer, &QMediaPlayer::positionChanged,
            this, &PlaybackHandler::positionChanged);
        connect(m_mediaPlayer, &QMediaPlayer::bufferStatusChanged,
            this, &PlaybackHandler::bufferStatusChanged);
        connect(m_mediaPlayer, &QMediaPlayer::mediaStatusChanged,
            this, &PlaybackHandler::mediaStatusChanged);
        connect(m_mediaPlayer, &QMediaPlayer::stateChanged,
            this, &PlaybackHandler::stateChanged);

        m_mediaPlayer->play();
    }

    virtual void stop()
    {
        m_mediaPlayer->stop();

        disconnect(m_mediaPlayer,
            static_cast<void (QMediaPlayer::*)(QMediaPlayer::Error)>(&QMediaPlayer::error), this, &PlaybackHandler::error);
        disconnect(m_mediaPlayer, &QMediaPlayer::stateChanged, this,
            &PlaybackHandler::stateChanged);
        disconnect(m_mediaPlayer, &QMediaPlayer::mediaStatusChanged, this,
            &PlaybackHandler::mediaStatusChanged);
        disconnect(m_mediaPlayer, &QMediaPlayer::bufferStatusChanged, this,
            &PlaybackHandler::bufferStatusChanged);
        disconnect(m_mediaPlayer, &QMediaPlayer::positionChanged, this,
            &PlaybackHandler::positionChanged);
        disconnect(m_mediaPlayer, &QMediaPlayer::durationChanged, this,
            &PlaybackHandler::durationChanged);
    }

    virtual void pause()
    {
        m_mediaPlayer->pause();
    }

    virtual void seek(qint64 position)
    {
        m_mediaPlayer->setPosition(position);
    }

    virtual void load(const Source *s)
    {
        m_source = s;
        Q_EMIT mediaStatusChanged(QMediaPlayer::MediaStatus::LoadedMedia);
    }

    virtual qint64 position() const
    {
        return m_mediaPlayer->position();
    }

    virtual qint64 duration() const
    {
        return m_mediaPlayer->duration();
    }

    virtual int supports(const Source *s) = 0;

};

#endif // PLAYBACKHANDLER_H
