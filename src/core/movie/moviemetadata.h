#ifndef MOVIEMETADATA_H
#define MOVIEMETADATA_H

#include <qobjectdefs.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qurl.h>

#include "../model/itemmetadata.h"

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MovieMetadata : public ItemMetadata
{
Q_OBJECT

Q_PROPERTY(int runtime READ runtime WRITE setRuntime NOTIFY runtimeChanged)
Q_PROPERTY(QString tagline READ tagline WRITE setTagline NOTIFY taglineChanged)
Q_PROPERTY(QStringList genres READ genres WRITE setGenres NOTIFY genresChanged)
Q_PROPERTY(QString country READ country WRITE setCountry NOTIFY countryChanged)
Q_PROPERTY(QStringList credits READ credits WRITE setCredits NOTIFY creditsChanged)
Q_PROPERTY(QStringList directors READ directors WRITE setDirectors NOTIFY directorsChanged)
Q_PROPERTY(QString studio READ studio WRITE setStudio NOTIFY studioChanged)
Q_PROPERTY(QUrl trailer READ trailer WRITE setTrailer NOTIFY trailerChanged)
Q_PROPERTY(QStringList actors READ actors WRITE setActors NOTIFY actorsChanged)

Q_SIGNALS:
    void runtimeChanged();
    void taglineChanged();
    void genresChanged();
    void countryChanged();
    void creditsChanged();
    void directorsChanged();
    void studioChanged();
    void trailerChanged();
    void actorsChanged();

private:
    int m_runtime;
    QString m_tagline;
    QStringList m_genres;
    QString m_country;
    QStringList m_credits;
    QStringList m_directors;
    QString m_studio;
    QUrl m_trailer;
    QStringList m_actors;

public:
    explicit MovieMetadata(QObject *parent = 0);
    virtual ~MovieMetadata() = default;

    const QStringList& actors() const;
    void setActors(const QStringList& actors);
    void addActor(const QString &actor);

    const QString& country() const;
    void setCountry(const QString& country);

    const QStringList& credits() const;
    void setCredits(const QStringList& credits);
    void addCredit(const QString& credit);

    const QStringList& directors() const;
    void setDirectors(const QStringList& directors);
    void addDirector(const QString& director);

    const QStringList& genres() const;
    void setGenres(const QStringList& genres);
    void addGenre(const QString& genre);

    int runtime() const;
    void setRuntime(int runtime);

    const QString& studio() const;
    void setStudio(const QString& studio);

    const QString& tagline() const;
    void setTagline(const QString& tagline);

    const QUrl& trailer() const;
    void setTrailer(const QUrl& trailer);
};

#endif // MOVIEMETADATA_H
