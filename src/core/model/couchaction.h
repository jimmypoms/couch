/*
 * couchaction.h
 *
 *  Created on: 23 Jan 2016
 *      Author: jimmypoms
 */

#ifndef COUCHACTION_H_
#define COUCHACTION_H_

#include <qobject.h>
#include <qobjectdefs.h>
#include <qstring.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT CouchAction : public QObject
{
Q_OBJECT

Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

Q_SIGNALS:
    void textChanged();
    void enabledChanged();
    void triggered();

private:
    QString m_text;
    bool m_enabled;

public:
    explicit CouchAction(QObject* parent = 0);
    virtual ~CouchAction() = default;

    bool enabled() const;
    void setEnabled(bool enabled);

    const QString& text() const;
    void setText(const QString& text);

public Q_SLOTS:
    virtual void trigger();
};

#endif /* COUCHACTION_H_ */
