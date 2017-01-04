/*
 * couchactionlist.h
 *
 *  Created on: 23 Jan 2016
 *      Author: jimmypoms
 */

#ifndef COUCHACTIONLIST_H_
#define COUCHACTIONLIST_H_

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
class CouchAction;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT CouchActionList : public QAbstractListModel
{
Q_OBJECT

Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
Q_PROPERTY(int length READ rowCount NOTIFY actionsChanged)

Q_SIGNALS:
    void loadingChanged();
    void actionsChanged();
    void actionsLoaded();

private:
    QString m_id;
    QList<std::shared_ptr<CouchAction> > m_actions;

    int m_loadingCount;
    std::atomic_int m_loaded;

public:
    CouchActionList(int loadingCount = 0, QString id = "");
    virtual ~CouchActionList() = default;

    const QString &id() const;
    bool loading() const;

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public Q_SLOTS:
    void addActions(const QList<std::shared_ptr<CouchAction> > &actions, const QString &id = "");
    void insert(int row, const std::shared_ptr<CouchAction> &action);
    void append(const QList<std::shared_ptr<CouchAction> > &actions);
    void append(const std::shared_ptr<CouchAction> &action);
    QList<std::shared_ptr<CouchAction> > actions() const;
};

#endif /* COUCHACTIONLIST_H_ */
