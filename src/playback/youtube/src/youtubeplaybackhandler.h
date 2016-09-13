#ifndef YOUTUBEPLAYBACKHANDLER_H
#define YOUTUBEPLAYBACKHANDLER_H

#include "couch/playbackhandler.h"

#include <qmap.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qobjectdefs.h>
#include <qstring.h>

class YoutubePlaybackHandler : public PlaybackHandler
{
Q_OBJECT

Q_PLUGIN_METADATA(IID "org.couch.playback.youtube")
Q_INTERFACES(PlaybackHandlerInterface)

private:
    enum Quality
    {
        FLV_240p = 5,
        MP4_360p = 18,
        MP4_720p = 22,
        FLV_360p = 34,
        FLV_480p = 35,
        MP4_1080p = 37,
        WEBM_360p = 43,
        WEBM_480p = 44,
        WEBM_720p = 45,
        WEBM_1080p = 46
    };
    static QString s_supportedHost;

    QNetworkAccessManager m_nam;

    QMap<int, QString> m_urlMap;
    QString m_urlTitle;
    QString m_origUrl;
    QString m_latestPreferredUrl;
    Quality m_preferredQuality;

    bool m_shouldPlay;
    bool m_replyFinished;

    QString findPreferredUrl();
    QString findPreferredUrl(const QMap<int, QString> &urlMap, Quality q);

public:
    YoutubePlaybackHandler();
    virtual ~YoutubePlaybackHandler() = default;
    virtual void load(const Source *source);
    virtual void play();
    int supports(const Source *source);

private Q_SLOTS:
    void onNetworkError(QNetworkReply::NetworkError error);
    void onNetworkResponse();
};

#endif // YOUTUBEPLAYBACKHANDLER_H
