/*
 * setting.h
 *
 *  Created on: 19 Mar 2017
 *      Author: jimmypoms
 */

#ifndef SETTING_H_
#define SETTING_H_

#include "setting.h"

#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>
#include <qvariant.h>

class Setting : public QObject
{
Q_OBJECT

Q_ENUMS(Type)
Q_PROPERTY(Type type READ type)
Q_PROPERTY(QString key READ key)
Q_PROPERTY(QVariant defaultValue READ defaultValue)
Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
Q_PROPERTY(QString title READ title NOTIFY titleChanged)
Q_PROPERTY(QString description READ description NOTIFY descriptionChanged)

public:
    enum Type
    {
        Folder
    };

private:
    Type m_type;
    QString m_key;
    QVariant m_defaultValue;
    QVariant m_value;
    QString m_title;
    QString m_description;

    virtual bool isValid(const QVariant &value) = 0;

Q_SIGNALS:
    void valueChanged();
    void titleChanged();
    void descriptionChanged();

public:
    explicit Setting(QObject *parent, Type type, QString key, QVariant defaultValue,
            QString title, QString description);
    virtual ~Setting() = default;

    Type type() const;
    const QString &key() const;
    const QString &title() const;
    const QString &description() const;
    const QVariant &defaultValue() const;

    const QVariant &value() const;
    void setValue(const QVariant &value);
};

#endif /* SETTING_H_ */
