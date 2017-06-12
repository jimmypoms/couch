/*
 * pluginloader.h
 *
 *  Created on: 25 Oct 2015
 *      Author: jimmypoms
 */

#ifndef PLUGINLOADER_H_
#define PLUGINLOADER_H_

#include <qcoreapplication.h>
#include <qdebug.h>
#include <qdir.h>
#include <qflags.h>
#include <qlogging.h>
#include <qobject.h>
#include <qpluginloader.h>
#include <qstring.h>
#include <qstringlist.h>
#include <functional>
#include <typeinfo>

template<class IFace>
class PluginLoader
{
    QObject *m_parent;

public:
    explicit PluginLoader(QObject *parent = 0) :
            m_parent(parent)
    {
    }
    virtual ~PluginLoader() = default;

    void load(const QString &subDir, std::function<void(IFace*)> a)
    {
        QDir pluginsDir(QCoreApplication::applicationDirPath());
#if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == "MacOS") {
            pluginsDir.cdUp();
            pluginsDir.cdUp();
            pluginsDir.cdUp();
        }
#elif defined(Q_OS_LINUX)
        if (pluginsDir.dirName() == "bin") {
            pluginsDir.cdUp();
            pluginsDir.cd("lib/couch");
        }
#endif
        if (!pluginsDir.cd(subDir)) {
            return;
        }
        qDebug() << "loading plugins in directory" << pluginsDir.absolutePath();
        for (QString fileName : pluginsDir.entryList(QDir::Files | QDir::NoSymLinks)) {
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName), m_parent);
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                IFace *interface = qobject_cast<IFace *>(plugin);
                if (interface) {
                    a(interface);
                } else {
                    qDebug() << "failed to cast interface" << fileName;
                }
            } else {
                qDebug() << pluginLoader.errorString();
            }
        }
    }

    void load(const QString &subDir, std::function<void(QObject*)> a)
    {
        QDir pluginsDir(QCoreApplication::applicationDirPath());
#if defined(Q_OS_WIN)
        if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
        if (pluginsDir.dirName() == "MacOS") {
            pluginsDir.cdUp();
            pluginsDir.cdUp();
            pluginsDir.cdUp();
        }
#elif defined(Q_OS_LINUX)
        if (pluginsDir.dirName() == "bin") {
            pluginsDir.cdUp();
            pluginsDir.cd("lib/couch");
        }
#endif
        if (!pluginsDir.cd(subDir)) {
            return;
        }
        qDebug() << "loading plugins in directory" << pluginsDir.absolutePath();
        for (QString fileName : pluginsDir.entryList(QDir::Files | QDir::NoSymLinks)) {
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName), m_parent);
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                QObject *interface = qobject_cast<QObject *>(plugin);
                if (interface) {
                    a(interface);
                } else {
                    qDebug() << "failed to cast interface" << fileName;
                }
            } else {
                qDebug() << pluginLoader.errorString();
            }
        }
    }
};

#endif /* PLUGINLOADER_H_ */
