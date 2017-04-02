/*
 * settinglist.h
 *
 *  Created on: 22 Mar 2017
 *      Author: jimmypoms
 */

#ifndef SETTINGLIST_H_
#define SETTINGLIST_H_

#include "setting.h"

#include <qabstractitemmodel.h>
#include <qhash.h>
#include <qlist.h>
#include <qobjectdefs.h>
#include <qsettings.h>
#include <qstring.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT SettingList : public QAbstractListModel
{
Q_OBJECT

private:
    QObject *m_object;
    const SettingList *m_parent;
    QString m_prefix;
    QString m_settingPrefix;
    QList<Setting*> m_settings;
    QHash<const QObject*, SettingList*> m_settingLists;
    QSettings m_qsettings;

    void write(Setting *setting);
    void load(Setting *setting);
    void insert(int, Setting *setting);
    const QString &settingPrefix() const;

public:
    SettingList(QObject *object, const SettingList *parent, QString prefix);
    virtual ~SettingList() = default;

    void appendSetting(Setting *setting);
    void prependSetting(Setting *setting);
    const QList<Setting*> &settings() const;

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void setSettingList(QObject *object, SettingList *setting);

    Q_INVOKABLE
    SettingList* settingList(QObject *object) const;

    void write();
    void load();
};

#endif /* SETTINGLIST_H_ */
