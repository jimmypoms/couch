#include "couch.h"

#include "couch/service.h"
#include "couch/settings/settinglist.h"

Couch::Couch(QObject *parent) :
        QObject(parent)
{
}

void Couch::addService(QObject* service)
{
    service->setParent(this);
    m_services.append(service);
}

const QList<QObject*>& Couch::services() const
{
    return m_services;
}

SettingList* Couch::buildSettings()
{
    SettingList* list = new SettingList(this, nullptr, "");

    for (QObject *object : m_services) {
        ServiceImpl *service = qobject_cast<ServiceImpl*>(object);
        if (service) {
            list->setSettingList(service, service->buildSettings(list));
        }
    }

    return list;
}
