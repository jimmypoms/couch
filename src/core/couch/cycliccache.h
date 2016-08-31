#ifndef CYCLICCACHE_H
#define CYCLICCACHE_H

#include "serializableclass.h"

#include <qdatastream.h>
#include <qdebug.h>
#include <qdir.h>
#include <qfile.h>
#include <qflags.h>
#include <qglobal.h>
#include <qhash.h>
#include <qiodevice.h>
#include <qlogging.h>
#include <qstandardpaths.h>
#include <qstring.h>
#include <cstddef>
#include <functional>
#include <memory>
#include <type_traits>
#include <unordered_map>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

namespace std
{
    template<>
    struct hash<QString> : public unary_function<QString, size_t>
    {
        size_t operator()(QString v) const
        {
            return qHash(v);
        }
    };
}

template<class Key, class T>
class COUCH_LIBRARY_EXPORT CyclicCache : public std::unordered_map<Key, std::shared_ptr<T>,
        std::hash<Key> >
{
    typedef std::unordered_map<Key, std::shared_ptr<T> > cyclic_cache_container_type;

    QString cacheFilePath;
    QString name;
    size_t maxSize;

    void load()
    {
        QFile file(cacheFilePath);
        if (!file.exists()) {
            QDir(cacheFilePath).mkpath("..");
        }

        file.open(QIODevice::ReadWrite);

        QDataStream in(&file);
        QString loadedName;
        in >> loadedName;
        if (loadedName == name) {
            qint32 size;
            in >> size;
            for (qint32 i = 0; i < size; ++i) {
                Key k;
                in >> k;
                T *v = new T();
                in >> *v;
                insert(k, v);
            }
            qDebug() << QString("%1 items loaded for cache '%2'").arg(QString::number(size), name);
        }
        file.close();
    }

    void save()
    {
        QFile file(cacheFilePath);

        file.open(QIODevice::WriteOnly | QIODevice::Truncate);

        QDataStream out(&file);
        out << name;
        qint32 size(cyclic_cache_container_type::size());
        out << size;
        for (auto i = cyclic_cache_container_type::cbegin();
                i != cyclic_cache_container_type::cend(); ++i) {
            T *item = static_cast<T*>((*i).second.get());
            if (item) {
                out << (*i).first;
                out << *item;
            }
        }
        file.close();
    }

public:
    CyclicCache(QString name, size_t size = 200) :
            cyclic_cache_container_type(), name(name), maxSize(size)
    {
        static_assert(std::is_base_of<SerializableClass, T>::value, "T is not a SerializableClass");
        QDir fileDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/cache");
        cacheFilePath = fileDir.absoluteFilePath(name);

        load();
    }

    ~CyclicCache()
    {
        save();
    }

    std::shared_ptr<T> insert(Key k, T* v)
    {
        if (cyclic_cache_container_type::size() >= maxSize) {
            cyclic_cache_container_type::erase(cyclic_cache_container_type::begin());
        }
        std::shared_ptr<T> vPtr(v);
        cyclic_cache_container_type::insert({k, vPtr});
        return vPtr;
    }
};

#endif // CYCLICCACHE_H
