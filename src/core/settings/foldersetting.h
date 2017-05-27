/*
 * foldersetting.h
 *
 *  Created on: 5 Apr 2017
 *      Author: jimmypoms
 */

#ifndef FOLDERSETTING_H_
#define FOLDERSETTING_H_

#include "setting.h"

#include <qstring.h>
#include <qvariant.h>

class FolderSetting : public Setting
{
Q_OBJECT

private:
    bool isValid(const QVariant &value);

public:
    explicit FolderSetting(QObject *parent, QString key, QVariant defaultValue, QString title,
            QString description);
    virtual ~FolderSetting() = default;
};

#endif /* FOLDERSETTING_H_ */
