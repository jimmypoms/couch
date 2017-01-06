#ifndef FILTER_H
#define FILTER_H

#include <qhash.h>
#include <qmetatype.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>

class CouchItemList;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT Filter : public QObject
{
Q_OBJECT

Q_ENUMS(Order)
Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
Q_PROPERTY(Filter::Order order READ order WRITE setOrder NOTIFY orderChanged)
Q_PROPERTY(int limit READ limit WRITE setLimit NOTIFY limitChanged)
Q_PROPERTY(int offset READ offset WRITE setOffset NOTIFY offsetChanged)
Q_PROPERTY(CouchItemList* result READ result NOTIFY resultChanged)
Q_PROPERTY(bool hasMore READ hasMore NOTIFY hasMoreChanged)

Q_SIGNALS:
    void textChanged();
    void orderChanged();
    void limitChanged();
    void offsetChanged();
    void dirtyChanged();
    void resultChanged();
    void hasMoreChanged();

public:
    enum Order
    {
        None,
        Popular,
        Newest
    };

private:
    QString m_text;
    Filter::Order m_order;
    int m_offset;
    int m_limit;
    bool m_dirty;
    CouchItemList *m_result;
    QHash<const QObject*, bool> m_hasMoreMap;

protected:
    void setDirty(bool dirty);

public:
    explicit Filter(QObject *parent = 0, int offset = 0, int limit = 20);
    virtual ~Filter() = default;

    const QString& text() const;
    void setText(const QString& text);

    Filter::Order order() const;
    void setOrder(Filter::Order m_order);

    int limit() const;
    void setLimit(int m_limit);

    int offset() const;
    void setOffset(int m_offset);

    bool isDirty() const;

    /** \brief Resets the Filter to it's initial state if it is dirty.
     *         If the Filter is not dirty this method does nothing.
     *
     * Resetting means:
     *  - resetting the hasMore internal values for providers
     *  - clearing the CouchItemList (beware of CouchItemList::clear() considerations)
     *  - setting the offset to zero
     *  - setting the dirty flag to false
     */
    void reset();

    CouchItemList* result() const;
    void setResult(CouchItemList* result);

    bool hasMore() const;

    /** \brief Returns true if the filter expects more results for a given provider.
     *
     * We do assume that there are more results when a provider has never
     * returned any results.
     */
    bool hasMore(const QObject* provider) const;
    void setHasMore(const QObject* provider, bool hasMore);
};

Q_DECLARE_METATYPE(const Filter*)
#endif // FILTER_H
