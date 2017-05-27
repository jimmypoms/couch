/*
 * foldersetting.cpp
 *
 *  Created on: 5 Apr 2017
 *      Author: jimmypoms
 */

#include "foldersetting.h"

#include <qdir.h>

FolderSetting::FolderSetting(QObject* parent, QString key, QVariant defaultValue, QString title,
        QString description) :
        Setting(parent, Type::Folder, key, defaultValue, title, description)
{
}

bool FolderSetting::isValid(const QVariant& value)
{
    return QDir(value.toString()).exists();
}
