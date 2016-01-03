#ifndef SERIALIZABLECLASS_H
#define SERIALIZABLECLASS_H

#include <qdatastream.h>
#include <qobject.h>
#include <qobjectdefs.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT SerializableClass : public QObject
{
Q_OBJECT

public:
    explicit SerializableClass(QObject *parent = 0);
};

QDataStream &operator<<(QDataStream &ds, const SerializableClass &obj);
QDataStream &operator>>(QDataStream &ds, SerializableClass &obj);

#endif // SERIALIZABLECLASS_H
