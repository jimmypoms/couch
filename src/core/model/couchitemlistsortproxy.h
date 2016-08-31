/*
 * couchitemlistsortproxy.h
 *
 *  Created on: 7 Aug 2016
 *      Author: jimmypoms
 */

#ifndef COUCHITEMLISTSORTPROXY_H_
#define COUCHITEMLISTSORTPROXY_H_

#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qsortfilterproxymodel.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT CouchItemListSortProxy : public QSortFilterProxyModel
{
Q_OBJECT

Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
Q_PROPERTY(int length READ rowCount NOTIFY itemsChanged)

Q_SIGNALS:
    void loadingChanged();
    void itemsChanged();

public:
    explicit CouchItemListSortProxy(QObject *parent = nullptr);
    virtual ~CouchItemListSortProxy() = default;

    bool loading() const;
    void setSourceModel(QAbstractItemModel *sourceModel) Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    void sort(Qt::SortOrder order = Qt::AscendingOrder);
};

#endif /* COUCHITEMLISTSORTPROXY_H_ */
