#include "couch.h"
#include "pluginloader.h"

#include "couch/couchplayer.h"
#include "couch/movie/movieservice.h"
#include "couch/music/musicservice.h"
#include "couch/playbackhandler.h"
#include "couch/provider.h"

#include <qglobal.h>
#include <qguiapplication.h>
#include <qobject.h>
#include <qqmlapplicationengine.h>
#include <qqmlcontext.h>
#include <qscreen.h>
#include <qurl.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    Couch couch;
    CouchPlayer player;

    PluginLoader<PlaybackHandler> playbackLoader;
    playbackLoader.load("playback", [&player](PlaybackHandler *h) {
        player.addPlaybackHandler(h);
    });

    MovieService movieService;
    movieService.setPlayer(&player);
    couch.addService(&movieService);
    PluginLoader<MovieProviderInterface> movieProviderLoader;
    movieProviderLoader.load("provider", [&movieService](QObject *p) {
        MovieProviderInterface *interface = qobject_cast<MovieProviderInterface *>(p);
        if (interface) {
            movieService.addProvider(p);
        }
    });

    MusicService musicService;
    musicService.setPlayer(&player);
    couch.addService(&musicService);
    PluginLoader<MusicProviderInterface> musicProviderLoader;
    musicProviderLoader.load("provider", [&musicService](QObject *p) {
        MusicProviderInterface *interface = qobject_cast<MusicProviderInterface *>(p);
        if (interface) {
            musicService.addProvider(p);
        }
    });

    qreal screenPixelDensity = QGuiApplication::primaryScreen()->physicalDotsPerInch()
            * QGuiApplication::primaryScreen()->devicePixelRatio();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(movieService.name(), &movieService);
    engine.rootContext()->setContextProperty(musicService.name(), &musicService);

    engine.rootContext()->setContextProperty("couch", &couch);
    engine.rootContext()->setContextProperty("player", &player);
    engine.rootContext()->setContextProperty("screenPixelDensity", screenPixelDensity);
    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}
