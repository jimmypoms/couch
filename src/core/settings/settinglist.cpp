/*
 * settingslist.cpp
 *
 *  Created on: 22 Mar 2017
 *      Author: jimmypoms
 */

#include "settinglist.h"

#include <qobject.h>
#include <qvariant.h>

SettingList::SettingList(QObject *object, const SettingList *parent, QString prefix) :
                QAbstractListModel(object), m_object(object), m_parent(parent), m_prefix(prefix),
                m_settingPrefix(prefix)
{
    if (m_parent) {
        m_settingPrefix = m_parent->settingPrefix() + '/' + m_prefix;
    }
}

void SettingList::write(Setting* setting)
{
    m_qsettings.setValue(settingPrefix() + '/' + setting->key(), setting->value());
}

void SettingList::load(Setting* setting)
{
    setting->setValue(
            m_qsettings.value(settingPrefix() + '/' + setting->key(), setting->defaultValue()));
}

void SettingList::insert(int row, Setting *setting)
{
    beginInsertRows(QModelIndex(), row, row);
    m_settings.insert(row, setting);
    connect(setting, &Setting::valueChanged, this, [=]() {
        this->write(setting);
    });
    endInsertRows();
}

void SettingList::prependSetting(Setting* setting)
{
    insert(0, setting);
}

void SettingList::appendSetting(Setting* setting)
{
    insert(rowCount(), setting);
}

const QList<Setting*>& SettingList::settings() const
{
    return m_settings;
}

QHash<int, QByteArray> SettingList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "modelData";
    return roles;
}

int SettingList::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_settings.count();
}

QVariant SettingList::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_settings.count()) {
        return QVariant::Invalid;
    }
    if (Qt::UserRole == role) {
        Setting *item = m_settings[index.row()];
        return QVariant::fromValue(item);
    }
    return QVariant::Invalid;
}

void SettingList::setSettingList(QObject* object, SettingList* setting)
{
    m_settingLists.insert(object, setting);
}

SettingList* SettingList::settingList(QObject* object) const
{
    SettingList* list = m_settingLists.value(object);

    if (!list) {
        for (auto settingList : m_settingLists) {
            list = settingList->settingList(object);
            if (list) {
                break;
            }
        }
    }

    return list;
}

const QString& SettingList::settingPrefix() const
{
    return m_settingPrefix;
}

void SettingList::write()
{
    for (auto setting : m_settings) {
        write(setting);
    }
    for (auto list : m_settingLists) {
        list->write();
    }
}

void SettingList::load()
{
    for (auto setting : m_settings) {
        load(setting);
    }
    for (auto list : m_settingLists) {
        list->load();
    }
}
