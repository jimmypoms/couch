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
    void setDirty(bool dirty);

    CouchItemList* result() const;
    void setResult(CouchItemList* result);

    bool hasMore() const;
    bool hasMore(const QObject* provider) const;
    void setHasMore(const QObject* provider, bool hasMore);
};

Q_DECLARE_METATYPE(const Filter*)
#endif // FILTER_H
