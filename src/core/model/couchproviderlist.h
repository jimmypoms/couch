/*
 * couchproviderlist.h
 *
 *  Created on: 3 Aug 2016
 *      Author: jimmypoms
 */

#ifndef COUCHPROVIDERLIST_H_
#define COUCHPROVIDERLIST_H_

#include <qabstractitemmodel.h>
#include <qobjectdefs.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT CouchProviderList : public QAbstractListModel
{
Q_OBJECT

private:
    QList<QObject*> m_providers;

public:
    CouchProviderList(QObject *parent = 0);
    virtual ~CouchProviderList() = default;

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

public Q_SLOTS:
    void insert(int row, QObject* provider);
    void append(const QList<QObject*> &providers);
    void append(QObject* provider);
};

#endif /* COUCHPROVIDERLIST_H_ */
