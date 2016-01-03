#include <qglobal.h>
#include <qguiapplication.h>
#include <qlist.h>
#include <qqmlapplicationengine.h>
#include <qqmlcontext.h>
#include <qscreen.h>
#include <qurl.h>

#include "couch/movie/movieprovider.h"
#include "couch/movie/movieservice.h"

#include "couch.h"
#include "pluginloader.h"

#include "playback/media/mediaplaybackhandler.h"
#include "playback/youtube/youtubeplaybackhandler.h"
#include "player/couchplayer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Couch couch;
    CouchPlayer player;

    PluginLoader<PlaybackHandler> playbackLoader;
    playbackLoader.load("playback", [&player](PlaybackHandler *h) {
        player.addPlaybackHandler(h);
    });
    MediaPlaybackHandler mediaHandler;
    YoutubePlaybackHandler youtubeHandler;
    player.addPlaybackHandler(&mediaHandler);
    player.addPlaybackHandler(&youtubeHandler);

    MovieService movieService;
    couch.addService(&movieService);
    PluginLoader<MovieProviderInterface> providerLoader;
    providerLoader.load("provider/movie", [&movieService](QObject *p) {
        movieService.addProvider(p);
    });

    qreal screenPixelDensity = QGuiApplication::primaryScreen()->physicalDotsPerInch()
            * QGuiApplication::primaryScreen()->devicePixelRatio();

    QQmlApplicationEngine engine;
    for (Service *s : couch.services()) {
        engine.rootContext()->setContextProperty(s->name(), s);
    }
    engine.rootContext()->setContextProperty("couch", &couch);
    engine.rootContext()->setContextProperty("player", &player);
    engine.rootContext()->setContextProperty("screenPixelDensity", screenPixelDensity);
    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}
