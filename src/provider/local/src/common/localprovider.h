/*
 * localprovider.h
 *
 *  Created on: 6 March 2016
 *      Author: jimmypoms
 */

#ifndef LOCALPROVIDER_H_
#define LOCALPROVIDER_H_

#include "couch/source.h"

#include <qchar.h>
#include <qdebug.h>
#include <qdir.h>
#include <qdiriterator.h>
#include <qlogging.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qtconcurrentrun.h> // IWYU pragma: keep
#include <qthread.h>
#include <qurl.h>
#include <sys/time.h>
#include <xapian.h>
#include <atomic>
#include <ctime>

template<class Item, class Filter>
class LocalProvider
{
private:
    QString m_database;
protected:
    Xapian::Database m_reader;
    std::atomic_bool m_isIndexing;

    void setLibraryPath(const QString &path);

    Xapian::MSet searchDatabase(const Item *item);
    Xapian::MSet searchDatabase(const Filter *filter);

private:
    static QString expandHomeDir(const QString &dir);
    void loadDatabase(const QString &path);

    virtual QStringList filenameFilters() const = 0;
    virtual Xapian::Query buildQuery(Xapian::QueryParser &qp, const Item *item) = 0;
    virtual Xapian::Query buildQuery(Xapian::QueryParser &qp, const Filter *filter) = 0;
    virtual void indexFile(Xapian::WritableDatabase &writer, Xapian::TermGenerator &indexer,
            Source &source) = 0;

public:
    explicit LocalProvider(const QString &database);
    virtual ~LocalProvider() = default;
};

template<class Item, class Filter>
inline LocalProvider<Item, Filter>::LocalProvider(const QString &database) :
        m_database(database), m_isIndexing(false)
{
    try {
        m_reader = Xapian::Database(m_database.toStdString());
    } catch (const Xapian::DatabaseOpeningError &e) {
        QDir().mkpath(m_database);
        Xapian::WritableDatabase writer(m_database.toStdString(), Xapian::DB_CREATE);
        writer.close();
        m_reader = Xapian::Database(m_database.toStdString());
    }
}

template<class Item, class Filter>
inline Xapian::MSet LocalProvider<Item, Filter>::searchDatabase(const Item *item)
{
    Xapian::QueryParser qp;
    Xapian::Stem stemmer("english");

    qp.set_stemmer(stemmer);
    qp.set_database(m_reader);
    qp.set_stemming_strategy(Xapian::QueryParser::STEM_SOME);

    Xapian::Query query = buildQuery(qp, item);
    Xapian::Enquire enquire(m_reader);
    enquire.set_query(query);

    qDebug() << "loading provider:" << QString::fromStdString(enquire.get_description());
    return enquire.get_mset(0, 10);
}

template<class Item, class Filter>
inline Xapian::MSet LocalProvider<Item, Filter>::searchDatabase(const Filter *filter)
{
    Xapian::QueryParser qp;
    Xapian::Stem stemmer("english");

    qp.set_stemmer(stemmer);
    qp.set_database(m_reader);
    qp.set_stemming_strategy(Xapian::QueryParser::STEM_SOME);

    Xapian::Query query = buildQuery(qp, filter);
    Xapian::Enquire enquire(m_reader);
    enquire.set_query(query);
    if (filter->order() != Filter::None) {
        enquire.set_sort_by_value_then_relevance(Filter::Popular, true);
        if (filter->order() == Filter::Newest) {
            enquire.set_sort_by_value_then_relevance(Filter::Newest, true);
        }
    }

    qDebug() << "loading provider:" << QString::fromStdString(enquire.get_description())
            << "offset:" << filter->offset() << "limit:" << filter->limit();
    return enquire.get_mset(filter->offset(), filter->limit());
}

template<class Item, class Filter>
inline QString LocalProvider<Item, Filter>::expandHomeDir(const QString &dir)
{
    if (dir.at(0) == '~') {
        return QDir::homePath() + dir.mid(1);
    }

    return dir;
}

template<class Item, class Filter>
inline void LocalProvider<Item, Filter>::setLibraryPath(const QString &path)
{
    QtConcurrent::run(this, &LocalProvider::loadDatabase, path);
}

template<class Item, class Filter>
inline void LocalProvider<Item, Filter>::loadDatabase(const QString &path)
{
    Xapian::WritableDatabase writer(m_database.toStdString(), Xapian::DB_OPEN);
    Xapian::TermGenerator indexer;
    Xapian::Stem stemmer("english");
    indexer.set_stemmer(stemmer);

    std::clock_t start;
    double duration;
    QString library = expandHomeDir(path);
    qDebug() << "starting indexing of files in library path:" << library;
    m_isIndexing = true;
    int count = 0;
    start = std::clock();

    writer.begin_transaction();
    for (auto i = writer.postlist_begin(""); i != writer.postlist_end(""); ++i) {
        writer.delete_document(*i);
    }
    QDirIterator it(library, filenameFilters(), QDir::Files,
            QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);
    while (it.hasNext()) {
        ++count;
        QString filePath = it.next();

        Source source;
        source.setUrl(QUrl::fromLocalFile(filePath));
        indexFile(writer, indexer, source);
    }
    writer.commit_transaction();

    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    m_isIndexing = false;
    qDebug() << "finished indexing" << count << "files in path:" << library << duration << 's';
}

#endif /* LOCALPROVIDER_H_ */
