/*
 * vodoprovider.cpp
 *
 *  Created on: 28 Oct 2015
 *      Author: jimmypoms
 */

#include "vodoprovider.h"

#include <qbytearray.h>
#include <qchar.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonvalue.h>
#include <qnetworkreply.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qurl.h>
#include <qurlquery.h>

#include "couch/couchrequest.h"
#include "couch/filter.h"
#include "couch/movie/movie.h"
#include "couch/movie/moviemetadata.h"

VodoProvider::VodoProvider(QObject* parent) :
        MovieNetworkProvider(parent, "vodo")
{
}

void VodoProvider::buildRequest(CouchRequest* request, const MovieFilter* filter) const
{
    QUrl url("http://butter.vodo.net/popcorn");
    QUrlQuery q;
    q.addQueryItem("limit", QString::number(filter->limit()));
    q.addQueryItem("offset", QString::number(filter->offset()));
    q.addQueryItem("order_by", "desc");
    Movie::Genre genre = filter->genre();
    if (genre) {
        q.addQueryItem("genre", Movie::genreToString(genre));
    }
    MovieFilter::Order order = filter->order();
    if (order != MovieFilter::Order::None) {
        q.addQueryItem("sort_by", orderToString(order));
    }
    if (!filter->text().isEmpty()) {
        q.addQueryItem("query_term", filter->text());
    }
    url.setQuery(q);
    request->setUrl(url);

}

void VodoProvider::buildRequest(CouchRequest* request, const Movie* movie) const
{
    // TODO:
}

QString VodoProvider::orderToString(MovieFilter::Order order) const
{
    switch (order) {
        case MovieFilter::None:
            return "";
        case MovieFilter::Newest:
            return "date_added";
        case MovieFilter::Popular:
            return "peers";
    }
    return "";
}

QString VodoProvider::playIcon() const
{
    return "";
}

SettingList* VodoProvider::buildSettings(const SettingList* parent)
{
    return nullptr;
}

QTranslator* VodoProvider::pluginTranslator(const QLocale& locale)
{
    return nullptr;
}

QList<Source*> VodoProvider::parseReply(QNetworkReply* reply) const
{
    QByteArray jsonData = reply->readAll();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject json = document.object();

    QList<Source*> sources;
    if (json.contains("status")) {
        QString msg(json["status"].toString());
        if (msg != "ok") {
//            Q_EMIT error(json["status_message"].toString());
            return sources;
        }
    }
    if (!json.contains("downloads")) {
        return sources;
    }
    QJsonArray jsonArray = json.value("downloads").toArray();

    for (const QJsonValue &value : jsonArray) {
        QJsonObject json = value.toObject();
        Source* source = new Source();
        MovieMetadata* metadata = new MovieMetadata();
        source->setItemMetadata(metadata);

        source->setQuality(json.value("Quality").toString());
        source->setSizeBytes(json.value("SizeByte").toInt());
        source->setUrl(json.value("TorrentUrl").toString());

        metadata->setRating(json.value("Rating").toInt() / 100.0);
        metadata->setImage(json.value("CoverImage").toString());
        metadata->setPopularity(json.value("Popularity").toInt() / 100.0);
        metadata->setRuntime(json.value("Runtime").toString().toInt());
        metadata->setDescription(json.value("Synopsis").toString().trimmed());
        metadata->setTagline(json.value("Tagline").toString().trimmed());
        metadata->setName(json.value("MovieTitleClean").toString());
        metadata->setYear(json.value("MovieYear").toString().toInt());
        metadata->setGenres(json.value("Genre").toString().split(','));

        sources.append(source);
    }
    return sources;
}
