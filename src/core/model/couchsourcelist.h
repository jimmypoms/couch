/*
 * couchsourcelist.h
 *
 *  Created on: 18 Oct 2015
 *      Author: jimmypoms
 */

#ifndef COUCHSOURCELIST_H_
#define COUCHSOURCELIST_H_

#include "source.h"

#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qhash.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <atomic>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT CouchSourceList : public QAbstractListModel
{
Q_OBJECT

Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
Q_PROPERTY(int length READ rowCount NOTIFY sourcesChanged)
Q_PROPERTY(const QObject* provider READ provider CONSTANT)

Q_SIGNALS:
    void loadingChanged();
    void sourcesChanged();
    void sourcesLoaded();

private:
    QString m_id;
    std::atomic_bool m_loading;

    const QObject* m_provider;
    QList<Source*> m_sources;

public:
    explicit CouchSourceList(const QObject* provider = 0, QString id = "");
    virtual ~CouchSourceList() = default;

    const QString &id() const;
    const QObject *provider() const;
    const QList<Source*> sources() const;
    bool loading() const;

    QList<Source*>::const_iterator cbegin() const;
    QList<Source*>::const_iterator cend() const;

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public Q_SLOTS:
    void addSources(const QList<Source*> &sources, const QString &id = "");
    void insert(int row, Source* source);
    void append(const QList<Source*> &sources);
    void append(Source* source);
};

#endif /* COUCHSOURCELIST_H_ */
