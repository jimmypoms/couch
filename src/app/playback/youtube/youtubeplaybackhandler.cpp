#include "youtubeplaybackhandler.h"

#include <qbytearray.h>
#include <qchar.h>
#include <qdebug.h>
#include <qlogging.h>
#include <qmediaplayer.h>
#include <qnamespace.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qregexp.h>
#include <qstringlist.h>
#include <qurl.h>
#include <qurlquery.h>

#include "couch/source.h"

QString YoutubePlaybackHandler::s_supportedHost("www.youtube.com");

YoutubePlaybackHandler::YoutubePlaybackHandler() :
        PlaybackHandler("youtube"), m_nam(this), m_preferredQuality(Quality::MP4_720p),
                m_shouldPlay(false), m_replyFinished(false)
{
}

void YoutubePlaybackHandler::load(const Source *source)
{
    QNetworkRequest request(QUrl(source->url()));
    request.setRawHeader("User-Agent", "Mozilla/5.0");
    request.setRawHeader("Accept",
            "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    request.setRawHeader("Upgrade-Insecure-Requests", "1");
    QByteArray host(source->url().host().toLocal8Bit());
    request.setRawHeader("Host", host);
    QNetworkReply *reply = m_nam.get(request);

    connect(reply, &QNetworkReply::finished, this, &YoutubePlaybackHandler::onNetworkResponse);
    connect(reply,
            static_cast<void (QNetworkReply::*)(
                    QNetworkReply::NetworkError)>(&QNetworkReply::error),
            this, &YoutubePlaybackHandler::onNetworkError);
}

void YoutubePlaybackHandler::play()
{
    if (m_mediaPlayer->state() == QMediaPlayer::PausedState) {
        m_mediaPlayer->play();
        return;
    }

    m_shouldPlay = true;
    if (m_replyFinished) {
        m_shouldPlay = false;
        m_replyFinished = false;

        connectPlayerError();
        connectPlayerSignals();

        m_mediaPlayer->play();
    }
}

int YoutubePlaybackHandler::supports(const Source *source)
{
    if (source->url().host() == s_supportedHost) {
        return 5;
    }
    return 0;
}

void YoutubePlaybackHandler::onNetworkError(QNetworkReply::NetworkError error)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    m_replyFinished = true;
    reply->deleteLater();
    qDebug() << "youtube network error:" << reply->errorString();
}

void YoutubePlaybackHandler::onNetworkResponse()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    m_replyFinished = true;

    m_urlMap.clear();
    QRegExp re("\"url_encoded_fmt_stream_map\"\\s*:\\s*\"([^\"]*)\"", Qt::CaseInsensitive,
            QRegExp::RegExp2);

    if (re.indexIn(reply->readAll()) != -1) {
        QString result = re.cap(1).replace(QString("\\u0026"), QString('&'));
        QUrlQuery query;
        for (const QString line : result.split(',')) {
            query.setQuery(line);
            QString itag = query.queryItemValue("itag");
            QString url = query.queryItemValue("url");
            if (!itag.isEmpty() && !url.isEmpty()) {
                m_urlMap[itag.toInt()] = QUrl::fromPercentEncoding(url.toLatin1());
            }
        }

        m_mediaPlayer->setMedia(QUrl(findPreferredUrl()));
        if (m_shouldPlay) {
            play();
        }
        Q_EMIT mediaStatusChanged(QMediaPlayer::MediaStatus::LoadedMedia);
    } else {
        qDebug() << "youtube playback error:"
                << "no 'url_encoded_fmt_stream_map' found in response";
        Q_EMIT error(QMediaPlayer::ResourceError);
    }

    reply->deleteLater();
}

QString YoutubePlaybackHandler::findPreferredUrl()
{
    m_latestPreferredUrl = findPreferredUrl(m_urlMap, m_preferredQuality);
    return m_latestPreferredUrl;
}

QString YoutubePlaybackHandler::findPreferredUrl(const QMap<int, QString>& urlMap, Quality q)
{
    // Choose a url according to preferred quality
    QString p_url;
    //Quality q = preferred_quality;

    if (q == MP4_1080p) {
        p_url = urlMap.value(MP4_1080p, QString());
        if (p_url.isNull())
            p_url = urlMap.value(WEBM_1080p, QString());
        if (p_url.isNull())
            q = MP4_720p;
    }

    if (q == WEBM_1080p) {
        p_url = urlMap.value(WEBM_1080p, QString());
        if (p_url.isNull())
            p_url = urlMap.value(MP4_1080p, QString());
        if (p_url.isNull())
            q = WEBM_720p;
    }

    if (q == MP4_720p) {
        p_url = urlMap.value(MP4_720p, QString());
        if (p_url.isNull())
            p_url = urlMap.value(WEBM_720p, QString());
        if (p_url.isNull())
            p_url = urlMap.value(WEBM_480p, QString());
        if (p_url.isNull())
            q = MP4_360p;
    }

    if (q == WEBM_720p) {
        p_url = urlMap.value(WEBM_720p, QString());
        if (p_url.isNull())
            p_url = urlMap.value(MP4_720p, QString());
        if (p_url.isNull())
            q = WEBM_480p;
    }

    if (q == WEBM_480p) {
        p_url = urlMap.value(WEBM_480p, QString());
        if (p_url.isNull())
            q = WEBM_360p;
    }

    if (q == MP4_360p) {
        p_url = urlMap.value(MP4_360p, QString());
        if (p_url.isNull())
            p_url = urlMap.value(WEBM_360p, QString());
        if (p_url.isNull())
            q = FLV_360p;
    }

    if (q == WEBM_360p) {
        p_url = urlMap.value(WEBM_360p, QString());
        if (p_url.isNull())
            p_url = urlMap.value(MP4_360p, QString());
        if (p_url.isNull())
            q = FLV_360p;
    }

    // FLV, low priority
    if (q == FLV_480p) {
        p_url = urlMap.value(FLV_480p, QString());
        if (p_url.isNull())
            q = FLV_360p;
    }

    if (q == FLV_360p) {
        p_url = urlMap.value(FLV_360p, QString());
        if (p_url.isNull())
            q = FLV_240p;
    }

    if (q == FLV_240p) {
        p_url = urlMap.value(q, QString());
    }

    return p_url;
}

