#ifndef COUCHPLAYER_H
#define COUCHPLAYER_H

#include "couchplaylist.h"
#include "playbackhandler.h"

#include <qglobal.h>
#include <qlist.h>
#include <qmediaplayer.h>
#include <qobjectdefs.h>
#include <memory>

class Item;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT CouchPlayer : public QObject
{
Q_OBJECT

Q_ENUMS(PlaybackStatus)
Q_ENUMS(SourceStatus)
Q_ENUMS(Error)
Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
Q_PROPERTY(qint64 position READ position WRITE seek NOTIFY positionChanged)
Q_PROPERTY(QMediaObject* mediaObject READ getMediaObject CONSTANT)
Q_PROPERTY(QString error READ errorString)
Q_PROPERTY(bool playing READ playing NOTIFY playbackStatusChanged)
Q_PROPERTY(bool paused READ paused NOTIFY playbackStatusChanged)
Q_PROPERTY(bool stopped READ stopped NOTIFY playbackStatusChanged)
Q_PROPERTY(PlaybackStatus playbackStatus READ playbackStatus NOTIFY playbackStatusChanged)
Q_PROPERTY(SourceStatus sourceStatus READ sourceStatus NOTIFY sourceStatusChanged)
Q_PROPERTY(Source* currentSource READ currentSource NOTIFY currentSourceChanged)
Q_PROPERTY(Item* currentItem READ currentItem NOTIFY currentItemChanged)
Q_PROPERTY(Item* playlistItem READ playlistItem NOTIFY playlistItemChanged)
Q_PROPERTY(bool hasNext READ hasNext NOTIFY hasNextChanged)
Q_PROPERTY(bool hasPrevious READ hasPrevious NOTIFY hasPreviousChanged)
Q_PROPERTY(bool hasPlaylist READ hasPlaylist NOTIFY hasPlaylistChanged)

public:
    enum PlaybackStatus
    {
        Playing,
        Paused,
        Stopped
    };
    enum SourceStatus
    {
        Ready,
        Buffering,
        Loading,
        Stalled,
        NoSource,
        InvalidSource,
        EndOfSource,
        Unknown
    };
    enum Error
    {
        NoError,
        ResourceError,
        FormatError,
        NetworkError,
        AccessDeniedError,
        HandlerMissingError,
        ServiceMissingError,
        NoSourceError,
        UnknownError
    };

Q_SIGNALS:
    void playbackStatusChanged(PlaybackStatus status);
    void sourceStatusChanged(SourceStatus status);
    void loadingStatusChanged(int percentFilled);
    void bufferStatusChanged(int percentFilled);
    void error(CouchPlayer::Error error);

    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);

    void currentSourceChanged();
    void currentItemChanged();
    void playlistItemChanged();

    void hasNextChanged();
    void hasPreviousChanged();
    void hasPlaylistChanged();

private:

    std::unique_ptr<QMediaPlayer> m_mediaPlayer;
    PlaybackHandler *m_handler;
    QList<PlaybackHandler*> m_handlers;
    CouchPlaylist m_playlist;

    PlaybackStatus m_playbackStatus;
    SourceStatus m_sourceStatus;
    Error m_lastError;

    Source *m_currentSource;
    Item *m_currentItem;
    Item *m_playlistItem;

    void setPlaybackStatus(PlaybackStatus status);
    void setSourceStatus(SourceStatus status);

    void setCurrentSource(Source *Source);
    void setCurrentItem(Item *item);
    void setPlaylistItem(Item *item);

    void updatePlaylist(Item *item);
    void addPlaylistSources(Item *item);

public:
    explicit CouchPlayer(QObject *parent = 0);
    virtual ~CouchPlayer() = default;

    void addPlaybackHandler(PlaybackHandler *handler);
    QMediaObject *getMediaObject();
    qint64 duration() const;
    qint64 position() const;
    QString errorString() const;
    PlaybackStatus playbackStatus() const;
    SourceStatus sourceStatus() const;

    Source* currentSource() const;
    Item* currentItem() const;
    Item* playlistItem() const;

    bool hasNext();
    bool hasPrevious();
    bool hasPlaylist();

    void load(const Source *source);
    bool playing();
    bool paused();
    bool stopped();

private Q_SLOTS:
    void onHandlerLoadingStatusChanged(int percentFilled);
    void onHandlerBufferStatusChanged(int percentFilled);
    void onHandlerMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onHandlerStateChanged(QMediaPlayer::State state);
    void onHandlerError(QMediaPlayer::Error error);

public Q_SLOTS:
    void play(QObject *object);
    void play(Item *item);
    void play(Source *source);
    void play();
    void togglePlay();
    void stop();
    void pause();
    void seek(qint64 position);
    void next();
    void previous();

};

#endif // COUCHPLAYER_H
