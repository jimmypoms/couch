#include "couch.h"
#include "pluginloader.h"

#include "couch/couchplayer.h"
#include "couch/movie/movieservice.h"
#include "couch/music/musicservice.h"
#include "couch/playbackhandler.h"
#include "couch/provider.h"

#include <execinfo.h>
#include <qguiapplication.h>
#include <qlocale.h>
#include <qobject.h>
#include <qqmlapplicationengine.h>
#include <qqmlcontext.h>
#include <qstring.h>
#include <qtranslator.h>
#include <qurl.h>
#include <signal.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>

/* This structure mirrors the one found in /usr/include/asm/ucontext.h */
typedef struct _sig_ucontext {
    unsigned long     uc_flags;
    struct ucontext   *uc_link;
    stack_t           uc_stack;
    struct sigcontext uc_mcontext;
    sigset_t          uc_sigmask;
} sig_ucontext_t;

void crit_err_hdlr(int sig_num, siginfo_t * info, void * ucontext) {
    void *             array[50];
    void *             caller_address;
    char **            messages;
    int                size, i;
    sig_ucontext_t *   uc;

    uc = (sig_ucontext_t *)ucontext;

    /* Get the address at the time the signal was raised */
    #if defined(__i386__) // gcc specific
    caller_address = (void *) uc->uc_mcontext.eip; // EIP: x86 specific
    #elif defined(__x86_64__) // gcc specific
    caller_address = (void *) uc->uc_mcontext.rip; // RIP: x86_64 specific
    #else
    #error Unsupported architecture. // TODO: Add support for other arch.
    #endif

    fprintf(stderr, "\n");

    if (sig_num == SIGSEGV)
        fprintf(stderr, "signal %d (%s), address is %p from %p\n",sig_num, strsignal(sig_num), info->si_addr,(void *)caller_address);
    else
        fprintf(stderr, "signal %d (%s)\n",sig_num, strsignal(sig_num));

    size = backtrace(array, 50);
    /* overwrite sigaction with caller's address */
    array[1] = caller_address;
    messages = backtrace_symbols(array, size);
    /* skip first stack frame (points here) */
    for (i = 1; i < size && messages != NULL; ++i) {
        fprintf(stderr, "[bt]: (%d) %s\n", i, messages[i]);
    }

    free(messages);

    exit(EXIT_FAILURE);
}

void installSignal(int __sig) {
    struct sigaction sigact;
    sigact.sa_sigaction = crit_err_hdlr;
    sigact.sa_flags = SA_RESTART | SA_SIGINFO;
    if (sigaction(__sig, &sigact, (struct sigaction *)NULL) != 0) {
        fprintf(stderr, "error setting signal handler for %d (%s)\n",__sig, strsignal(__sig));
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    installSignal(SIGSEGV);

    QGuiApplication app(argc, argv);

    QTranslator translator;
    if (translator.load(QLocale(), "app", "_", ":/translations", ".qm")) {
        app.installTranslator(&translator);
    }

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

    QQmlApplicationEngine engine;
    engine.addImportPath(app.applicationDirPath() + "/../imports");

    engine.rootContext()->setContextProperty(movieService.name(), &movieService);
    engine.rootContext()->setContextProperty(musicService.name(), &musicService);

    engine.rootContext()->setContextProperty("couch", &couch);
    engine.rootContext()->setContextProperty("player", &player);
    engine.load(QUrl("qrc:/Application.qml"));

    return app.exec();
}
