#include "couchplayer.h"

#include "couch/couchproviderlist.h"
#include "couch/couchsourcelist.h"
#include "couch/item.h"
#include "couch/source.h"

#include <qdebug.h>
#include <qlogging.h>
#include <qobject.h>
#include <qurl.h>
#include "couch/couchitemlist.h" // IWYU pragma: keep

CouchPlayer::CouchPlayer(QObject *parent) :
                QObject(parent), m_mediaPlayer(new QMediaPlayer()), m_handler(nullptr),
                m_playlist(this), m_playbackStatus(PlaybackStatus::Stopped),
                m_sourceStatus(SourceStatus::NoSource), m_lastError(Error::NoError),
                m_currentSource(nullptr), m_currentItem(nullptr), m_playlistItem(nullptr)
{
}

void CouchPlayer::addPlaybackHandler(PlaybackHandler *handler)
{
    handler->setParent(this);
    m_handlers.push_back(handler);

    connect(handler, &PlaybackHandler::positionChanged, this, &CouchPlayer::positionChanged);
    connect(handler, &PlaybackHandler::durationChanged, this, &CouchPlayer::durationChanged);
    connect(handler, &PlaybackHandler::bufferStatusChanged, this,
            &CouchPlayer::onHandlerBufferStatusChanged);
    connect(handler, &PlaybackHandler::mediaStatusChanged, this,
            &CouchPlayer::onHandlerMediaStatusChanged);
    connect(handler, &PlaybackHandler::stateChanged, this, &CouchPlayer::onHandlerStateChanged);
    connect(handler, &PlaybackHandler::error, this, &CouchPlayer::onHandlerError);

    handler->setMediaPlayer(m_mediaPlayer.get());
}

void CouchPlayer::setPlaybackStatus(CouchPlayer::PlaybackStatus status)
{
    if (m_playbackStatus != status) {
        m_playbackStatus = status;
        Q_EMIT playbackStatusChanged(m_playbackStatus);
    }
}

void CouchPlayer::setSourceStatus(CouchPlayer::SourceStatus status)
{
    if (m_sourceStatus != status) {
        m_sourceStatus = status;
        Q_EMIT sourceStatusChanged(m_sourceStatus);
    }
}

QMediaObject *CouchPlayer::getMediaObject()
{
    return m_mediaPlayer.get();
}

QString CouchPlayer::errorString() const
{
    if (m_lastError == Error::HandlerMissingError) {
        return "no handler registered to play source";
    }
    return m_mediaPlayer->errorString();
}

CouchPlayer::PlaybackStatus CouchPlayer::playbackStatus() const
{
    return m_playbackStatus;
}

CouchPlayer::SourceStatus CouchPlayer::sourceStatus() const
{
    return m_sourceStatus;
}

qint64 CouchPlayer::duration() const
{
    if (m_handler) {
        return m_handler->duration();
    }
    return 0;
}

qint64 CouchPlayer::position() const
{
    if (m_handler) {
        return m_handler->position();
    }
    return 0;
}

void CouchPlayer::play(QObject *object)
{
    Item *item = qobject_cast<Item*>(object);
    if (item) {
        return play(item);
    }
    Source *source = qobject_cast<Source*>(object);
    if (source) {
        setPlaylistItem(nullptr);
        return play(source);
    }
}

void CouchPlayer::play(Source *source)
{
    load(source);
    setCurrentSource(source);
    setCurrentItem(qobject_cast<Item*>(source->parent()));
    Q_EMIT hasPreviousChanged();
    Q_EMIT hasNextChanged();
    play();
}

void CouchPlayer::play(Item* item)
{
    setPlaylistItem(item);
    play(m_playlist.first());
}

void CouchPlayer::play()
{
    if (!currentSource()) {
        Q_EMIT error(Error::NoSourceError);
        return;
    }
    m_handler->play();
}

void CouchPlayer::togglePlay()
{
    if (playing()) {
        pause();
    } else {
        play();
    }
}

void CouchPlayer::stop()
{
    if (m_handler) {
        m_handler->stop();
        m_handler = nullptr;
    }
    setPlaybackStatus(PlaybackStatus::Stopped);
    setSourceStatus(SourceStatus::NoSource);
    setCurrentSource(nullptr);
    setCurrentItem(nullptr);
}

void CouchPlayer::pause()
{
    if (m_handler) {
        m_handler->pause();
    }
}

void CouchPlayer::seek(qint64 position)
{
    if (m_handler) {
        m_handler->seek(position);
    }
}

Source* CouchPlayer::currentSource() const
{
    return m_currentSource;
}

Item* CouchPlayer::currentItem() const
{
    return m_currentItem;
}

void CouchPlayer::setCurrentSource(Source *source)
{
    if (m_currentSource != source) {
        m_currentSource = source;
        Q_EMIT currentSourceChanged();
    }
}

void CouchPlayer::setCurrentItem(Item *item)
{
    if (m_currentItem != item) {
        m_currentItem = item;
        Q_EMIT currentItemChanged();
    }
}

void CouchPlayer::setPlaylistItem(Item* item)
{
    if (m_playlistItem != item) {
        m_playlistItem = item;
        updatePlaylist(item);
        Q_EMIT playlistItemChanged();
        Q_EMIT hasPlaylistChanged();
    }
}

void CouchPlayer::updatePlaylist(Item *item)
{
    m_playlist.clear();

    if (item) {
        addPlaylistSources(item);
    }
}

void CouchPlayer::addPlaylistSources(Item *item)
{
    CouchProviderList* providers = item->providers();
    if (providers->rowCount()) {
        m_playlist.addSource(*(item->sources(*(providers->cbegin()))->cbegin()));
    }
    CouchItemList* itemList = item->childItems();
    if (itemList) {
        for (std::shared_ptr<Item> child : *itemList) {
            addPlaylistSources(child.get());
        }
    }
}

Item* CouchPlayer::playlistItem() const
{
    return m_playlistItem;
}

bool CouchPlayer::hasNext()
{
    return m_playlist.hasNext();
}

void CouchPlayer::next()
{
    if (hasNext()) {
        play(m_playlist.next());
    }
}

bool CouchPlayer::hasPrevious()
{
    return m_playlist.hasPrevious();
}

bool CouchPlayer::hasPlaylist()
{
    return m_playlistItem;
}

void CouchPlayer::previous()
{
    if (hasPrevious()) {
        play(m_playlist.previous());
    }
}

void CouchPlayer::load(const Source *source)
{
    int quality = 0;
    for (PlaybackHandler* h : m_handlers) {
        int tmp = 0;
        if ((tmp = h->supports(source)) > quality) {
            quality = tmp;
            m_handler = h;
        }
    }
    if (!m_handler) {
        m_lastError = Error::HandlerMissingError;
        Q_EMIT error(m_lastError);
        return;
    }
    m_handler->load(source);
    qDebug() << "source url" << source->url().toString() << "set to play with handler:"
            << m_handler->name();
}

bool CouchPlayer::playing()
{
    return m_playbackStatus == PlaybackStatus::Playing;
}

bool CouchPlayer::paused()
{
    return m_playbackStatus == PlaybackStatus::Paused;
}

bool CouchPlayer::stopped()
{
    return m_playbackStatus == PlaybackStatus::Stopped;
}

void CouchPlayer::onHandlerLoadingStatusChanged(int percentFilled)
{
    if (static_cast<QObject*>(m_handler) != sender()) {
        return;
    }
    Q_EMIT loadingStatusChanged(percentFilled);
}

void CouchPlayer::onHandlerBufferStatusChanged(int percentFilled)
{
    if (static_cast<QObject*>(m_handler) != sender()) {
        return;
    }
    Q_EMIT bufferStatusChanged(percentFilled);
}

void CouchPlayer::onHandlerMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (static_cast<QObject*>(m_handler) != sender()) {
        return;
    }
    switch (status) {
        case QMediaPlayer::UnknownMediaStatus:
            setSourceStatus(SourceStatus::Unknown);
            break;
        case QMediaPlayer::NoMedia:
            setSourceStatus(SourceStatus::NoSource);
            break;
        case QMediaPlayer::LoadedMedia:
            setSourceStatus(SourceStatus::Ready);
            break;
        case QMediaPlayer::LoadingMedia:
            setSourceStatus(SourceStatus::Loading);
            break;
        case QMediaPlayer::BufferedMedia:
            setSourceStatus(SourceStatus::Ready);
            break;
        case QMediaPlayer::BufferingMedia:
            setSourceStatus(SourceStatus::Buffering);
            break;
        case QMediaPlayer::StalledMedia:
            setSourceStatus(SourceStatus::Stalled);
            break;
        case QMediaPlayer::EndOfMedia:
            setSourceStatus(SourceStatus::EndOfSource);
            break;
        case QMediaPlayer::InvalidMedia:
            setSourceStatus(SourceStatus::InvalidSource);
            break;
        default:
            break;
    }
}

void CouchPlayer::onHandlerStateChanged(QMediaPlayer::State state)
{
    if (static_cast<QObject*>(m_handler) != sender()) {
        return;
    }
    switch (state) {
        case QMediaPlayer::StoppedState:
            setPlaybackStatus(PlaybackStatus::Stopped);
            break;
        case QMediaPlayer::PlayingState:
            setPlaybackStatus(PlaybackStatus::Playing);
            break;
        case QMediaPlayer::PausedState:
            setPlaybackStatus(PlaybackStatus::Paused);
            break;
        default:
            break;
    }
}

void CouchPlayer::onHandlerError(QMediaPlayer::Error e)
{
    if (static_cast<QObject*>(m_handler) != sender()) {
        return;
    }
    switch (e) {
        case QMediaPlayer::ResourceError:
            m_lastError = Error::ResourceError;
            break;
        case QMediaPlayer::NetworkError:
            m_lastError = Error::NetworkError;
            break;
        case QMediaPlayer::FormatError:
            m_lastError = Error::FormatError;
            break;
        case QMediaPlayer::AccessDeniedError:
            m_lastError = Error::AccessDeniedError;
            break;
        case QMediaPlayer::ServiceMissingError:
            m_lastError = Error::ServiceMissingError;
            break;
        default:
            m_lastError = Error::UnknownError;
            break;
    }
    Q_EMIT error(m_lastError);
    qDebug() << "handler error" << errorString();
}
