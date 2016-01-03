#include "serializableclass.h"

#include <qmetaobject.h>
#include <qvariant.h>

SerializableClass::SerializableClass(QObject *parent) :
        QObject(parent)
{
}

QDataStream &operator<<(QDataStream &ds, const SerializableClass &obj)
{
    for (int i = 0; i < obj.metaObject()->propertyCount(); ++i) {
        if (obj.metaObject()->property(i).isStored(&obj)) {
            ds << obj.metaObject()->property(i).read(&obj);
        }
    }
    return ds;
}

QDataStream &operator>>(QDataStream &ds, SerializableClass &obj)
{
    QVariant var;
    for (int i = 0; i < obj.metaObject()->propertyCount(); ++i) {
        if (obj.metaObject()->property(i).isStored(&obj)) {
            ds >> var;
            obj.metaObject()->property(i).write(&obj, var);
        }
    }
    return ds;
}

