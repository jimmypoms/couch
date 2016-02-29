/*
 * couchlist.h
 *
 *  Created on: 15 Oct 2015
 *      Author: jimmypoms
 */

#ifndef COUCHITEMLIST_H_
#define COUCHITEMLIST_H_

#include <qabstractitemmodel.h>
#include <qbytearray.h>
#include <qhash.h>
#include <qlist.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <atomic>
#include <memory>

class Item;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT CouchItemList : public QAbstractListModel
{
Q_OBJECT

Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
Q_PROPERTY(int length READ rowCount NOTIFY itemsChanged)

Q_SIGNALS:
    void loadingChanged();
    void itemsChanged();
    void itemsLoaded();

private:
    QString m_id;
    QList<std::shared_ptr<Item> > m_items;

    int m_loadingCount;
    std::atomic_int m_loaded;

public:
    CouchItemList(int loadingCount, QString id = "");
    virtual ~CouchItemList() = default;

    const QString &id() const;
    bool loading() const;

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public Q_SLOTS:
    void addItems(const QList<std::shared_ptr<Item> > &items, const QString &id = "");
    void insert(int row, const std::shared_ptr<Item> &item);
    void append(const QList<std::shared_ptr<Item> > &items);
    void append(const std::shared_ptr<Item> &item);
};

#endif /* COUCHITEMLIST_H_ */
