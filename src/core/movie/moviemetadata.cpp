#include "moviemetadata.h"

#include <qlist.h>

MovieMetadata::MovieMetadata(QObject *parent) :
        ItemMetadata(parent), m_runtime(0)
{
}

const QStringList& MovieMetadata::actors() const
{
    return m_actors;
}

void MovieMetadata::setActors(const QStringList &actors)
{
    if (m_actors != actors) {
        m_actors = actors;
        Q_EMIT actorsChanged();
    }
}

void MovieMetadata::addActor(const QString &actor)
{
    this->m_actors.append(actor);
    Q_EMIT actorsChanged();
}

const QString& MovieMetadata::country() const
{
    return m_country;
}

void MovieMetadata::setCountry(const QString& country)
{
    if (m_country != country) {
        m_country = country;
        Q_EMIT countryChanged();
    }
}

const QStringList& MovieMetadata::credits() const
{
    return m_credits;
}

void MovieMetadata::setCredits(const QStringList& credits)
{
    if (m_credits != credits) {
        m_credits = credits;
        Q_EMIT creditsChanged();
    }
}

void MovieMetadata::addCredit(const QString& credit)
{
    this->m_credits.append(credit);
    Q_EMIT creditsChanged();
}

const QStringList& MovieMetadata::directors() const
{
    return m_directors;
}

void MovieMetadata::setDirectors(const QStringList& directors)
{
    if (m_directors != directors) {
        m_directors = directors;
        Q_EMIT directorsChanged();
    }
}

void MovieMetadata::addDirector(const QString& director)
{
    this->m_directors.append(director);
    Q_EMIT directorsChanged();
}

const QStringList& MovieMetadata::genres() const
{
    return m_genres;
}

void MovieMetadata::setGenres(const QStringList& genres)
{
    if (m_genres != genres) {
        m_genres = genres;
        Q_EMIT genresChanged();
    }
}

void MovieMetadata::addGenre(const QString& genre)
{
    this->m_genres.append(genre);
    Q_EMIT genresChanged();
}

int MovieMetadata::runtime() const
{
    return m_runtime;
}

void MovieMetadata::setRuntime(int runtime)
{
    if (m_runtime != runtime) {
        m_runtime = runtime;
        Q_EMIT runtimeChanged();
    }
}

const QString& MovieMetadata::studio() const
{
    return m_studio;
}

void MovieMetadata::setStudio(const QString& studio)
{
    if (m_studio != studio) {
        m_studio = studio;
        Q_EMIT studioChanged();
    }
}

const QString& MovieMetadata::tagline() const
{
    return m_tagline;
}

void MovieMetadata::setTagline(const QString& tagline)
{
    if (m_tagline != tagline) {
        m_tagline = tagline;
        Q_EMIT taglineChanged();
    }
}

const QUrl& MovieMetadata::trailer() const
{
    return m_trailer;
}

void MovieMetadata::setTrailer(const QUrl& trailer)
{
    if (m_trailer != trailer) {
        m_trailer = trailer;
        Q_EMIT trailerChanged();
    }
}
