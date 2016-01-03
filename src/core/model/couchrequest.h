/*
 * couchrequest.h
 *
 *  Created on: 18 Oct 2015
 *      Author: jimmypoms
 */

#ifndef COUCHREQUEST_H_
#define COUCHREQUEST_H_

#include <qbytearray.h>
#include <qnetworkaccessmanager.h>
#include <qobjectdefs.h>
#include <qurl.h>

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT CouchRequest : public QObject
{
Q_OBJECT

Q_PROPERTY(QNetworkAccessManager::Operation operation READ operation WRITE setOperation NOTIFY operationChanged)
Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
Q_PROPERTY(QByteArray data READ data WRITE setData NOTIFY dataChanged)

Q_SIGNALS:
    void operationChanged();
    void urlChanged();
    void dataChanged();

private:
    QNetworkAccessManager::Operation m_operation;
    QUrl m_url;
    QByteArray m_data;

public:
    CouchRequest();
    virtual ~CouchRequest() = default;

    const QByteArray& data() const;
    void setData(const QByteArray& m_data);

    QNetworkAccessManager::Operation operation() const;
    void setOperation(QNetworkAccessManager::Operation m_operation);

    const QUrl& url() const;
    void setUrl(const QUrl& m_url);
};

#endif /* COUCHREQUEST_H_ */
